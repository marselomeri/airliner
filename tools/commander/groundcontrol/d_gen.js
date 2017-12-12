var doxygen = require('doxygen');
var userOptions = {
    OUTPUT_DIRECTORY: "docs",
    INPUT: "./",
    RECURSIVE: "YES",
    FILE_PATTERNS: ["*.js", "*.md"],
    EXTENSION_MAPPING: "js=Javascript",
    GENERATE_LATEX: "NO",
    EXCLUDE_PATTERNS: ["*/node_modules/*"]
};

doxygen.createConfig(userOptions);
doxygen.run();