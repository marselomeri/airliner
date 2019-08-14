#!/usr/bin/node
/****************************************************************************
*
*   Copyright (c) 2019 Windhover Labs, L.L.C. All rights reserved.
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


var mergeJSON = require( 'merge-json' );
var fs = require( 'fs' );
var argv = require( 'minimist' )( process.argv.slice( 2 ) );

/* mergejs cli utility*/
/**
 * Show help text for cli
 */
var displayHelp = function() {
  console.log( 'mergejs -a <Input JSON file> -b <Input JSON file> -o <output file>' );
}

/**
 * validate option 'a' in cli
 * @param  {Object} argv cli argument variable
 */
if ( argv.hasOwnProperty( 'a' ) == false ) {
  console.log( 'Missing "-a"' );
  displayHelp();
  process.exit( -1 );
}

/**
 * validate option 'b' in cli
 * @param  {Object} argv cli argument variable
 */
if ( argv.hasOwnProperty( 'b' ) == false ) {
  console.log( 'Missing "-b"' );
  displayHelp();
  process.exit( -1 );
}

/**
 * validate option 'o' in cli
 * @param  {Object} argv cli argument variable
 */
if ( argv.hasOwnProperty( 'o' ) == false ) {
  console.log( 'Missing "-o"' );
  displayHelp();
  process.exit( -1 );
}

/* merge two input files */
var inputA = JSON.parse( fs.readFileSync( argv.a, 'utf8' ) );
var inputB = JSON.parse( fs.readFileSync( argv.b, 'utf8' ) );

var output = mergeJSON.merge( inputA, inputB );

/* store output file in specified location */
fs.writeFile( argv.o, JSON.stringify( output, null, 4 ), 'utf8', function( err ) {
  if ( err ) throw err;
} );
