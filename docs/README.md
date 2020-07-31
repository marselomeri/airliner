### To build. 

This is known to work with Python 3.5

1. `virtualenv -p python3.5 venv`
2. `pip install sphinx`
3. `pip install sphinx-rtd-theme`
4. `pip install breathe`
5. `pip install sphinxcontrib-doxylink`
6. `pip install graphviz`
7. From the repository base directory `make docs`

To open up the documentation you can run this command ` xdg-open /home/vagrant/git/airliner/build/reference/default/docs/html/index.html `

These were generated by a tool called `breathe-apidoc` which parses xml doxygen-generated files to rst files and enables us to link to structs/classes/data structures that exists on our doxygen docs with very simple syntax from rst files.