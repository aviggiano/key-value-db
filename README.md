# key-value-db
This project contains different implementations of hash maps

Currently developed:
  1.  Using a Binary Search Tree as underlying data structure
  2.  Using a Dynamic resizing array as underlying data structure

## Dependencies:
  This project depends on:
  1.  [googletest](https://github.com/google/googletest) 
  2.  [valgrind](http://valgrind.org/)

## Building
1.  `$ ./configure.sh`
  This step will simply init the git submodule for googletest
2.  `$ make`

## Testing
To Run all unit tests, use:

    $ make test
 
To Run all tests using valgrind, use:

    $ make test-valgrind`
    
## Running

    $ ./key-value-db # runs on port 8888
  
## Commands (the semicolon is necessary)

`CREATE key value;`

  Creates new element 'key' with value 'value'

`READ key;`

  Returns value of element 'key'

`UPDATE key new-value;`

  Updates value of element 'key' to 'new-value'

`DELETE key;`

  Deletes element 'key'

## Using netcat to send commants

    $ echo "CREATE mykey myvalue;" | netcat -q 1 127.0.0.1 8888
    $ echo "READ mykey;" | netcat -q 1 127.0.0.1 8888
