
Problem: Index error for google mock but it compiles correctly. It is because some defines are in the C++11 but the eclipse does not set it.
Solution: Add __cplusplus=201103L to use C++11.
How to:
  1. Select the project -> right click in mouse -> Properties -> C/C++ General -> Preprocessor Include Paths, Macros etc. -> Providers tab: Move Up the "CDT User Setting Entries" to be the first item (top item), and the "CDT GCC Built-in Compiler Settings" to be second item (below the top item);
  2. "CDT User Setting Entries" and the "CDT GCC Built-in Compiler Settings" shall be enabled (selected);
  3. Go to Entries tab -> Select "GNU C++" -> Select "CDT User Setting Entries" -> Add... button -> Select Preprocessor Macro -> In the Name field, type: __cplusplus -> In the value field, type: 201103L -> Press OK -> Apply -> Apply and Close
  4. Refresh;
  5. Select the project -> right click in mouse -> Index -> Rebuild.
