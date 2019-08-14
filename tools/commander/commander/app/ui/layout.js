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

'use strict';

/**
 * A global variable which will store GoldenLayout instance and can be
 * passes around to be used by andy other functionality
 * @type {GoldenLayout}
 */
var myLayout;

/**
 * Initiailization routine required by GoldenLayout
 * @param       {GoldenLayout} mlyt GoldenLayout object
 * @constructor
 */
function InitLayout( mlyt ) {
  /* Register Component in layout */
  mlyt.registerComponent( 'Blank', function( container, state ) {
    if ( state.link ) {
      container.getElement().load( state.link );
    } else {
      container.getElement().html( '<h2>' + state.text + '</h2>' );
    }
    $( window ).on( "LayoutSaved", function() {
      container.extendState( {
        link: container._config.componentState.link
      } );
    } );
  } );
  mlyt.init();
  
  setTimeout(function () {
      BindCdrDataToVariableServer(myLayout.container);
  }, 1000);

  /*  handles for when itemCreated, tabsCreated, stackCreadted
   * stateChanged events are triggered by myLayout */
  mlyt.on( "itemCreated", function(item) {
    if ( item.type == "component" ) {
      try {
        link = item.config.componentState.link;
        item.container._contentElement.load( link );
        item.container._contentElement.css( "overflow", "auto" );
      } catch ( e ) {
        //cu.logError( 'itemCreated | cannot load link onto component' )
      }
    }
  } );

  mlyt.on( "stateChanged", function(obj) {
      $(document).trigger('commander-layout-changed');
  } );
}

/**
 * Browser starts donwloading the laout as .lyt file
 * @constructor
 */
function SaveLayout() {
  /* now save the state */
  let form = $( "[id='inputField0']" );
  let name = "";
  if ( form.val() != "" ) {
    name = form.val();
    name = name.replace( / /g, '_' );
  }
  var components = myLayout.root.getItemsByType( 'component' );
  for ( var i = 0; i < components.length; i++ ) {
    if ( components[ i ].config.title == 'Dataplot' ) {
      var apl = components[ i ].element.find( '.active-plot-list-content' );
      components[ i ].config.componentState.PlotDef = apl.data( 'PlotDef' );
    }
  }


  /* stringify state config */
  var cfg = myLayout.toConfig();
  /* add database */
  cfg.database = cu.getDatabase();
  let state = JSON.stringify( cfg, null, ' ' );
  var blob = new Blob( [ state ], {
    type: "text/json;charset=utf-8"
  } );
  saveAs( blob, name + '.lyt' );
  cu.logInfo( 'Layout | saved layout as', name );
}

/**
 * Loads a .lyt file to layout
 * @constructor
 */
function LoadLayout() {
  UnbindCdrDataFromVariableServer(myLayout.container);
  session.unsubscribeAll();
  
  var files = document.getElementById( 'browse0' ).files;
  var reader = new FileReader();
  reader.onload = ( function( theFile ) {
    return function( e ) {
      try {
        var savedState = JSON.parse( e.target.result );
        if ( savedState !== null ) {
          myLayout.destroy()
          myLayout = new window.GoldenLayout( savedState, $( '#cdr-layout-container' ) );
          updateDragSources();
          window.dispatchEvent( llc );
          InitLayout( myLayout );
          cu.logInfo( 'Layout | loaded from local drive' )
          if ( savedState.hasOwnProperty( 'database' ) ) {
            cu.clearDatabase();
            for ( var e in savedState.database ) {
              cu.addRecord( e, savedState.database[ e ] )
            }
          } else {
            cu.logError( 'Layout | loaded configuration has no database' )
          }
        } else {
          cu.logError( 'Layout | could not be loaded' )
        }
      } catch ( ex ) {
        cu.logError( 'Layout | exception in reading file ' + ex );
      }
    }
  } )( files[ 0 ] );
  reader.readAsText( files[ 0 ] );
}

/**
 * Update callback for layout in navtree
 * @param       {Object} node    node
 * @param       {Object} display display
 * @constructor
 */
function UpdateLayoutNode( node, display ) {
  session.getLayouts( node.path, function( dirEntries ) {
    var layoutEntries = [];
    /* modify dirEntries */
    for ( var entryID in dirEntries ) {
      var dirEntry = dirEntries[ entryID ];
      var layoutEntry = {
        name: '/' + entryID,
        text: dirEntry.shortDescription,
        longDescription: dirEntry.longDescription,
        path: node.path + '/' + entryID,
        href: node.path + '/' + entryID,
        handlebarsContext: dirEntry.handlebarsContext
      };
      if ( dirEntry.hasOwnProperty( 'nodes' ) ) {
    	layoutEntry.selectable = false;
    	layoutEntry.checkable = false;
        layoutEntry.lazyLoad = true;
      } else {
        layoutEntry.icon = 'fa fa-th-large'
        layoutEntry.type = 'config';
        layoutEntry.href = window.location.origin + window.location.pathname + '#' + node.path.replace(/^\/+/, '') + '/' + entryID;
        layoutEntry.enableLinks = true;
    	layoutEntry.selectable = true;
    	layoutEntry.checkable = false;
        layoutEntry.lazyLoad = false;
      }

      layoutEntries.push( layoutEntry );
    }
    var tree = $( '#cdr-layout-menu-container' ).treeview( true );
    tree.addNode( layoutEntries, node, node.index, {
      enableLinks: true
    } );
  } );
}

/**
 * Update callback for panel in navtree
 * @param       {Object} node    node
 * @param       {Object} display display
 * @constructor
 */
function UpdatePanelNode( node, display ) {
  session.getPanels( node.path, function( dirEntries ) {
    var panelEntries = [];
    /* modify dirEntries */
    for ( var entryID in dirEntries ) {
      var dirEntry = dirEntries[ entryID ];
      var panelEntry = {
        name: '/' + entryID,
        text: dirEntry.shortDescription,
        longDescription: dirEntry.longDescription,
        path: node.path + '/' + entryID,
        href: node.path + '/' + entryID,
        selectable: true,
        checkable: false,
        handlebarsContext: dirEntry.handlebarsContext
      };
      if ( dirEntry.hasOwnProperty( 'nodes' ) ) {
        panelEntry.lazyLoad = true;
        panelEntry.selectable = false;
      } else {
        panelEntry.icon = 'fa fa-file';
        panelEntry.lazyLoad = false;
        panelEntry.selectable = true;
        panelEntry.type = 'file';
        panelEntry.url = node.path + '/' + entryID
      }
      panelEntries.push( panelEntry );
    }
    var tree = $( '#cdr-panel-menu-container' ).treeview( true )
    tree.addNode( panelEntries, node, node.index, {
      silent: true
    } );
    tree.expandNode( node, {
      silent: true,
      ignoreChildren: true
    } );
  } );
}

/**
 * Update callback for panel in navtree
 * @param       {Object} node    node
 * @param       {Object} display display
 * @constructor
 */
function UpdateWidgetNode( node, display ) {
  session.getWidgets( node.path, function( dirEntries ) {
    var panelEntries = [];
    /* modify dirEntries */
    for ( var entryID in dirEntries ) {
      var dirEntry = dirEntries[ entryID ];
      var panelEntry = {
        name: '/' + entryID,
        text: dirEntry.shortDescription,
        longDescription: dirEntry.longDescription,
        path: node.path + '/' + entryID,
        href: node.path + '/' + entryID,
        selectable: false,
        checkable: false,
        handlebarsContext: dirEntry.handlebarsContext
      };
      if ( dirEntry.hasOwnProperty( 'nodes' ) ) {
        panelEntry.lazyLoad = true;
        panelEntry.selectable = false;
      } else {
        panelEntry.icon = 'fa fa-code';
        panelEntry.lazyLoad = false;
        panelEntry.selectable = true;
        panelEntry.type = 'file';
        panelEntry.url = node.path + '/' + entryID
      }
      panelEntries.push( panelEntry );
    }
    var tree = $( '#cdr-widget-menu-container' ).treeview( true )
    tree.addNode( panelEntries, node, node.index, {
      silent: true
    } );
    tree.expandNode( node, {
      silent: true,
      ignoreChildren: true
    } );
  } );
}