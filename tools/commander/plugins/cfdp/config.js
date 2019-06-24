/****************************************************************************
 *
 *   Copyright (c) 2018 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Windhover Labs nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

var convict = require( 'convict' );

/**
 * Define cfdp-database schema
 * @type {Object}
 */
var config = convict( {
  env: {
    doc: 'The application environment.',
    format: [ 'production', 'development', 'test' ],
    default: 'development',
    env: 'NODE_ENV'
  },
  AckTimeout: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 10
  },
  AckLimit: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 2
  },
  NakTimeout: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 5
  },
  NakLimit: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 3
  },
  InactivityTimeout: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 20
  },
  OutgoingFileChunkSize: {
      doc: 'Path for cfdp engine to store temporary files',
      format: 'int',
      default: 64
  },
  SaveIncompleteFiles: {
      doc: 'Path for cfdp engine to store temporary files',
      format: Boolean,
      default: false
  },
  MyID: {
      doc: 'Path for cfdp engine to store temporary files',
      format: String,
      default: '0.23'
  },
  TempDir: {
      doc: 'Path for cfdp engine to store temporary files',
      format: String,
      default: '/tmp/cf/'
  },
  CfdpClientStreamID: {
      doc: 'Stream ID for cfdp queries',
      format: String,
      default: ''
  },
  CfdpInputStream: {
      doc: 'Stream ID for listening to binary data',
      format: String,
      default: ''
  },
  CfdpOutputStream: {
      doc: 'Stream ID for sending to binary data',
      format: String,
      default: ''
  },
  RX: [ {
	  PhyBasePath: {
	      doc: 'Path to the base directory',
	      format: String,
	      default: ''
	  },
	  SourcePath: {
	      doc: 'Source base path',
	      format: String,
	      default: '/'
	  },
	  RetainFailures: {
	      doc: 'Set to true to retain partial files from failed transactions.',
          format: Boolean,
          default: false
	  },
	  Overwrite: {
	      doc: 'Set to true to automatically a file if the file already exists.',
          format: Boolean,
          default: false
	  },
	  CreateSubDirectories: {
	      doc: 'Automatically create subdirectories as needed.',
          format: Boolean,
          default: false
	  }
  } ],
  TX: [ {
	  TransactionClass: {
	      doc: 'Set to 1 or 2.',
          format: 'int'
	  },
	  PhyBasePath: {
	      doc: 'Path to the base directory',
	      format: String,
	      default: ''
	  },
	  DeleteOnSuccess: {
	      doc: 'Set to true to retain partial files from failed transactions.',
          format: Boolean,
          default: false
	  },
	  DestinationPath: {
	      doc: 'Set to true to automatically a file if the file already exists.',
          format: String
	  },
	  CreateSubDirectories: {
	      doc: 'Automatically create subdirectories as needed.',
          format: Boolean,
          default: true
	  }
  } ]
} );

module.exports = config;