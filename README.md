# key-value-db

This project contains a key-value store that supports CRUD operations over a simple TCP message protocol.

## Dependencies:
  
This project depends on:
  
1.  [googletest](https://github.com/google/googletest) 
2.  [valgrind](http://valgrind.org/)

## Building

1.  `$ ./configure.sh` # initializes googletest submodule
2.  `$ make` # compiles the server

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

## Using netcat to send commands

    $ echo "CREATE mykey myvalue;" | netcat -q 1 127.0.0.1 8888
    $ echo "READ mykey;" | netcat -q 1 127.0.0.1 8888
