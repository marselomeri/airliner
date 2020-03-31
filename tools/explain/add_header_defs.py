"""
 
    Copyright (c) 2019 Windhover Labs, L.L.C. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
 
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
  3. Neither the name Windhover Labs nor the names of its contributors 
     may be used to endorse or promote products derived from this software
     without specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

"""

import argparse
import json
import os
import sqlite3
import struct
from abc import abstractmethod, ABCMeta
from collections import namedtuple, OrderedDict
from csv import writer
from io import RawIOBase
from time import time
from typing import Type, Dict, Tuple, Any, Union

from explain.explain_error import ExplainError
from explain.map import SymbolMap
from explain.elf_reader import ElfReader
from explain.sql import SQLiteBacked
from explain.symbol import Symbol





def check_format_arg(value):
    ivalue = int(value)
    if ivalue < 1 or ivalue > 3:
        raise argparse.ArgumentTypeError("%s is an invalid time format." % value)
    return ivalue


def main():
    parser = argparse.ArgumentParser()
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument('--database', default=':memory:',
                        help='database to read from')
    parser.add_argument('--ccsds', help='CCSDS input file')
    parser.add_argument('--time-format', help='time format [1=CFE_SB_TIME_32_16_SUBS, 2=CFE_SB_TIME_32_32_SUBS, 3=CFE_SB_TIME_32_32_M_20]', required=True, type=check_format_arg)

    args = parser.parse_args()

    pri_header_size = 6

    # The size of the telemetry secondary header depends on the time format.  Set the size now.
    tlm_sec_header_size = 0;
    if args.time_format == 1:
        tlm_sec_header_size = 6
    else:
        tlm_sec_header_size = 8

    cmd_sec_header_size = 2

    database = sqlite3.connect(args.database)

    cur = database.cursor()

    with open(args.ccsds) as fp:
       # First get the IDs to the intrisic types that we'll need later, starting with uint32
       cur.execute("SELECT * FROM symbols WHERE name = 'uint32'")    
       row = cur.fetchone()
       uint32_id = int(row[0])

       # Get the uint16 ID
       cur.execute("SELECT * FROM symbols WHERE name = 'uint16'")    
       row = cur.fetchone()
       uint16_id = int(row[0])

       # Iterate through the structures defined in our input file.
       for msg_id, struct_name in json.load(fp).items():
           # Get the database entry for this symbol.
           cur.execute("SELECT * FROM symbols WHERE name = '%s'" % struct_name)
           row = cur.fetchone()
           if row != None:
               symbol_id = row[0]
               byte_size = row[1]
           
               is_command_msg = int(msg_id, 0) & 0x1000;

               if is_command_msg:
                   # This is a command message.  Delete the primary and secondary headers
                   cur.execute("DELETE FROM fields WHERE symbol = %u AND byte_offset < %u" % (symbol_id, pri_header_size + cmd_sec_header_size))    
                   database.commit()
               else:
                   cur.execute("DELETE FROM fields WHERE symbol = %u AND byte_offset < %u" % (symbol_id, pri_header_size + tlm_sec_header_size))     
                   database.commit()

               # Insert the Stream ID definition.
               cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity, little_endian) VALUES(%u,'%s',%u,%u,%u, 0)" % (symbol_id, 'CCSDS_StreamID', 0, uint16_id, 0))
               database.commit()

               # Insert the Sequence definition.
               cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity, little_endian) VALUES(%u,'%s',%u,%u,%u, 0)" % (symbol_id, 'CCSDS_Sequence', 2, uint16_id, 0))
               database.commit()

               # Insert the Length definition.
               cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity, little_endian) VALUES(%u,'%s',%u,%u,%u, 0)" % (symbol_id, 'CCSDS_Length', 4, uint16_id, 0))
               database.commit()

               if is_command_msg:
                   # This is a command message.  Add the Command secondary header.
                   cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity) VALUES(%u,'%s',%u,%u,%u)" % (symbol_id, 'CCSDS_Command', pri_header_size, uint16_id, 0))
                   database.commit()
               else:
                   # This is a telemetry message.  Add the Seconds telemetry field.
                   cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity) VALUES(%u,'%s',%u,%u,%u)" % (symbol_id, 'CCSDS_Time_Seconds', pri_header_size, uint32_id, 0))
                   database.commit()
 
                   # The subseconds field depends on the time format.
                   if args.time_format == 1:
                       # This is CFE_SB_TIME_32_16_SUBS
                       cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity) VALUES(%u,'%s',%u,%u,%u)" % (symbol_id, 'CCSDS_Time_Subseconds', (pri_header_size + 4), uint16_id, 0))
                   else:
                       # This is either CFE_SB_TIME_32_16_SUBS or CFE_SB_TIME_32_32_M_20.  Either way, its the same bit length.
                       cur.execute("INSERT INTO fields(symbol, name, byte_offset, type, multiplicity) VALUES(%u,'%s',%u,%u,%u)" % (symbol_id, 'CCSDS_Time_Subseconds', (pri_header_size + 4), uint32_id, 0))
                   database.commit()


if __name__ == '__main__':
    main()
    # print(
    #     'This is an abstract script. Users should subclass StreamParser in\n'
    #     'their own code and may then optionally call the main method of this\n'
    #     'script to invoke some basic command line parsing.')
    # exit(0)
