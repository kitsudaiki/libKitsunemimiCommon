# libKitsunemimiCommon

![Gitlab pipeline status](https://img.shields.io/gitlab/pipeline/tobiasanker/libKitsunemimiCommon?label=build%20and%20test&style=flat-square)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/tobiasanker/libKitsunemimiCommon?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/tobiasanker/libKitsunemimiCommon?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-14-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

This library contains some functions, I need for my other projects. There are functions for memory-handling, thread-handling, data representation and testing.

### Content Overview

#### Data-Items

*include-file:* `libKitsunemimiCommon/common_items/data_items.h`

These are classes for data-representation and comparable to the dict-objects of python. The data-items were originally the core data handling structure inside libKitsunemimiJson for representing json-trees. Thats why the string output of these items still have json-format. The table-items are for table styled output of information. Internally it use the data-items.

#### Tables

*include-file:* `libKitsunemimiCommon/common_items/table_item.h`

This is for printing tables. Internally it use the data-items for handling the content. For example you could parse the json-formated content of an http message via libKitsunemimiJson, use the the resulting data-item-tree together with a header definition and print is as table. The results looks for example like this:

```
+-----------------+---------+
| Name of column1 | column2 |
+=================+=========+
| this is a test  | k       |
+-----------------+---------+
| another test    | asdf    |
+-----------------+---------+
| x               |         |
| y               |         |
| z               |         |
+-----------------+---------+
```

#### Data buffer

*include-file:* `libKitsunemimiCommon/buffer/data_buffer.h`

This is a simple buffer for binary-data. The primary advantage is the easier resizing when adding new data. Internally it uses alligned memory, because this is necessary for the direct read- and write-operations of the libKitsunemimiPersistence.

#### Ring buffer

*include-file:* `libKitsunemimiCommon/buffer/ring_buffer.h`

Ring buffer to fast continuously read and write data. Its actually used as buffer for incoming messages in the network library libKitsunemimiNetwork for fast message-caching.

#### Stack buffer

*include-file:* `libKitsunemimiCommon/buffer/stack_buffer.h`

Stack of multiple data-buffer together with a reserve-class to avoid unnecessary memory allocation.

#### Threads

*include-file:* `libKitsunemimiCommon/threading/thread.h`

This class is only a collection of some thread-function like blocking and so on which I often use. This makes the creation of threads more easy for me. Additionally this class provides the ability to bind a new one of this thread to a specific cpu-thread.

#### Threads

*include-file:* `libKitsunemimiCommon/threading/barrier.h`

This class can block a number of threads and release automatically, if all have reached the barrier. To avoid dead-lock, they can also released manually.

#### Tests

*include-file:* `libKitsunemimiCommon/test_helper/compare_test_helper.h` and `libKitsunemimiCommon/test_helper/speed_test_helper.h`

These are little test-helper classes which provides basic functionallity for unit- and benchmark-tests.

#### Statemachine

*include-file:* `libKitsunemimiCommon/statemachine.h`

It's only a simple statemachine in the moment. Basically its only to change the state and check the current state. It doesn't trigger any events after changing the state.

#### Common methods

*include-file:* `libKitsunemimiCommon/common_methods/string_methods.h` and `libKitsunemimiCommon/common_methods/vector_methods.h`

These contains some commonly used mehtods for strings and vectors, like for example replace substrings within a string.

## Common Information aboud my projects

Here some common information about my projects and my code-styling. It's not complete and a bit short. I will write a styling-guide for my projects, where I will write this a bit longer with more explanation, why I make it like this.

## Build

### Requirements

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | 6.x | Compiler for the C++ code.
qmake | qt5-qmake | 5.x | This package provides the tool qmake, to build the project

Installation on Ubuntu/Debian:

```bash
sudo apt-get install g++ qt5-qmake
```

IMPORTANT: All my projects are only tested on Linux. 

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/tobiasanker/libKitsunemimiCommon.git
cd libKitsunemimiCommon
./build.sh
cd ../result
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Usage

Its a shord overview of the most important functions of the library. If even with this something is unclear, than please write me a mail or an issue.

### Common items

Here is a short documentation of the functions of the items. It doesn't descibe all functions, because the most should be self explaining in the header-files, like remove, add and so on. 

#### data-items

There exist three different items which all inherit the `DataItem` for generic access:

- `DataValue`
    - simple value-item
    - can be string, int-value or float-value
- `DataMap`
    - This is a map-object for key-value-pair with a string as identifier and a DataItem-pointer as value
    - data can be added with the `insert`-method
- `DataArray`
    - It's a internally a vector of Dataitem-pointer
    - data can be added with the `append`-method

IMPORTANT: all getter here only return a pointer to the internal object. If you want a copy, you have to use the `copy`-method of the objects to recursivly the data-item-tree behind the pointer.

To see all offered possebilities, which are provided by the data-items, please see the header-file `common_items/data_items.h`. There is nearly all self-explaining, because there are basically only getter and setter. So the following is only a minimal example:

```cpp
#include <libKitsunemimiCommon/common_items/data_items.h>

// init some value
DataValue stringValue("test");
DataValue intValue(42);
DataValue floatValue(42.5f);

// init and fill array
DataArray array;
array.append(stringValue.copy());
array.append(intValue.copy());
array.append(floatValue.copy());
array.append(nullptr);

// init and fill map
DataMap map;
map.insert("asdf", stringValue.copy());
map.insert("hmm", intValue.copy());
map.insert("xyz", floatValue.copy());

// add the array also to the map
map.insert("array", array.copy());

int size = map.size();
// `size` is 4 (3 values and 1 array)


std::string output = map.toString(true);
/**
`output` would look like this:

{
    "asdf": "test",
    "hmm": 42,
    "xyz": 42.500000,
    "array": [
        "test",
        42,
        42.500000,
        null
    ]
}
**/

std::string value = map.get("array")->get(2)->toValue()->toString();
// `value` would be `42.500000` as string
```

#### table-items

This is for printing informations as table on the commandline in form of this example:

```
+-----------------+---------+
| Name of column1 | column2 |
+=================+=========+
| this is a test  | k       |
+-----------------+---------+
| asdf            | hmmm    |
+-----------------+---------+
| x               |         |
| y               |         |
| z               |         |
+-----------------+---------+
```

Its primary to print informations coming from a REST-API response in form a json. So it can be filled manually or with content which was parsed with libKitsunemimiJson (coming soon open-source). If the content of a cell of the table contains a string with line breaks, its shown as multiple lines line in the last row of the example.

- manual filling of the table:

```cpp
#include <libKitsunemimiCommon/common_items/table_item.h>


TableItem testItem;

// add columes
// first value is the internal used name to identify the values in the content.
// the second value is the name for the output. If this is not set, it uses the internal name here too.
testItem.addColumn("column1", "Name of column1");
testItem.addColumn("column2");

testItem.addRow(std::vector<std::string>{"this is a test", "k"});
testItem.addRow(std::vector<std::string>{"asdf", "qwert"});

// convert to string
std::string output = testItem.toString();
/**
here ouput has nwo the content: 

"+-----------------+---------+\n"
"| Name of column1 | column2 |\n"
"+=================+=========+\n"
"| this is a test  | k       |\n"
"+-----------------+---------+\n"
"| asdf            | hmmm    |\n"
"+-----------------+---------+\n";
**/

```

- fill with predefined informations:

```cpp
#include <libKitsunemimiCommon/common_items/table_item.h>

DataArray header;
/**
content of the header in form of:

[
    {
        "inner": "column1",
        "outer": "Name of column1"
    },
    {
        "inner": "column2",
        "outer": "column2"
    }
]
**/

DataArray body;
/**
content of the body in form of:

[
    {
        "column1": "this is a test",
        "column2": "k"
    },
    {
        "column1": "asdf",
        "column2": "qwert"
    }
]
**/

// initialize the table-item with the predefined body and header
// The header is not required here. The columns can be added afterwards.
TableItem testItem(&body, &header);

std::string output = testItem.toString();
/**
here ouput has now the content: 

"+-----------------+---------+\n"
"| Name of column1 | column2 |\n"
"+=================+=========+\n"
"| this is a test  | k       |\n"
"+-----------------+---------+\n"
"| asdf            | hmmm    |\n"
"+-----------------+---------+\n";
**/

```

The width of a column is per default limited to 500 characters. Its possible to modify this, by calling the toString-methods with a value. For example `testItem.toString(10)` to limit the width of a column to 10 characters. If the content of a cell of the table is longer than this value, line breaks will be added and write it in multiple lines.

It is also possible to convert it into a vertical table. The it is returned a table with two columns. The left is the header in vertical form and the right column is the first row of the table in vertical form. It makes tables with only one row better readable. Example:

```cpp
TableItem testItem();
/** following content
"+-----------------+---------+\n"
"| Name of column1 | column2 |\n"
"+=================+=========+\n"
"| this is a test  | k       |\n"
"+-----------------+---------+\n"
"| asdf            | hmmm    |\n"
"+-----------------+---------+\n";
**/


std::string output = testItem.toString(100, true);
/**
first argument it the maximum size of the column and the secont is the alternative vertical mode
here ouput has now the content: 

"+-----------------+----------------+\n"
"| Name of column1 | this is a test |\n"
"+-----------------+----------------+\n"
"| column2         | k              |\n"
"+-----------------+----------------+\n";

One the first row is used here for the output
**/

```


### Data Buffer

The data-buffer is only a struct with some external functions for easier byte-buffer-handling. The internal byte-array is a alligned memory with a size of a multiple of the defined block-size. This is necessary for direct read- and write-operations to the storage. Beside this, the struct contains the current size of the buffer in number of bytes and number of allocated blocks. It is possible to use the `data` as mormal byte-array for read and write operations or use the `addData` and `getBlock` for access. The `addData` allocates automatically the required number of block, if the buffer is not big enough. 

```cpp
#include <libKitsunemimiCommon/buffer/data_buffer.h>

// initialize new data-buffer with 10 x 4KiB
DataBuffer testBuffer(10);

int value = 42;

// write data to buffer a the position pointed by the value `testBuffer.bufferPosition`
// you can set the bufferPosition directly to write at a custom location
// or write your data directly with memcpy to any position of `testBuffer.data`
bool success = addData(&testBuffer, &value);

// This example is a bit pointless, because it is the first value in the data-buffer
// It get the block with id 0 from the buffer as int-array and from with it gets the first element
int readValue = static_cast<int>(getBlock(&testBuffer, 0))[0];

// write data to buffer a the position pointed by the value `testBuffer.bufferPosition`
bool success = addDataToBuffer(&testBuffer, static_cast<void*>(value), sizeof(int);

// additional allocate 10 more block
success = allocateBlocks(&testBuffer, 10);

// clear the buffer and reduce it to 10 block again
success = resetBuffer(&testBuffer, 10);

```

### Ring Buffer

// TODO

### Stack Buffer

// TODO

### Threads

The usage can be explained with the following examples:

- This is the basic look of a new class, which should run in a separate thread:

```cpp
// demo_thead.h

#include <libKitsunemimiCommon/thread.h>


class DemoThread 
    : public Kitsunemimi::Thread
{

public:
    DemoThread();

    void run()
    {
        while(!m_abort)
        {
            if(m_block) {
                blockThread();
            }
            // do something
        }
    }
}
```

- It can be called like this for example:

```cpp
#include <libKitsunemimiCommon/demo_thead.h>

int main()
{
    // create a thread which is binded to cpu-thread with id 1
    DemoThread testThread(1);

    // start thread
    testThread.start();

    // let the thrad pause the next time the next time it start the while-loop from beginning
    testThread.initBlockThread();

    // let the thread continue its work
    testThread.continueThread();

    // stop the thread and wait until he has finished his work
    testThread.stop();

    return 0;
}
```

### Compare Tests

For using the unit-tests your test-class have to inherit the class `Kitsunemimi::CompareTestHelper` and give the header fo the constructur a name for the test as string. Inside the single tests you can than call the two macros `TEST_EQUAL(<VARIABLE_TO_CHECK> , <EXPECTED_VALUE);` and `TEST_NOT_EQUAL(<VARIABLE_TO_CHECK> , <NOT_EXPECTED_VALUE);`. First is successful when equal and second one is successful, when unequal. 

- After a success the result would look like this:

```cpp
------------------------------
start <name of the tests>

tests succeeded: <number of successful tests>
tests failed: <number of failed tests>
------------------------------
```

- When a test failed, the output looks like this:

```cpp
Error in Unit-Test
   File: "<file-path where thre failed test is located>"
   Method: "<method name where thre failed test is located>"
   Line: "<line-number of the failed test inside the test-class>"
   Variable: "<name of the tested variable>"
   Should-Value: "<Value which is originally expected in the variable>"
   Is-Value: "<Value of the tested variable>"
```

HINT: this output is only as intelligent as `std::cout`, so for example if you test an `uint8_t`-value, then cast it to int at first, to see the is-value in the error-output. 

Example:

- Header-file:

```cpp
// demo_test.h

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class Demo_Test 
    : public Kitsunemimi::CompareTestHelper    // <-- connect with unit-tests
{
public:
    Demo_Test();

private:
    void some_test();
};
```

- Source-file:

```cpp
#include "demo_test.h"

Demo_Test::Demo_Test() 
    : Kitsunemimi::CompareTestHelper("Demo_Test")    // <-- give the unit-test a name
{
    some_test();    // <-- call the test-method
}

/**
 * some_test
 */
void
DataBuffer_Test::some_test()
{
    int answerForAll = 42;

    // compare two values
    // first the is-value 
    // second the should-value
    TEST_EQUAL(answerForAll, 42);   // <-- single test

    // inverted test
    TEST_NOT_EQUAL(answerForAll, 0);
}
```

The result would be:

```
------------------------------
start Demo_Test

tests succeeded: 2
tests failed: 0
------------------------------
```

For more examples you could also use the tests in the test-directory of this repository.


### Statemachine

This is really a ultra simple statemachine, so the few functions can easily explained by the following example.


```cpp

#include <libKitsunemimiCommon/statemachine.h>

enum states
{
    SOURCE_STATE = 1,
    TARGET_STATE = 2,
    CHILD_STATE = 3,
    NEXT_STATE = 4,
    GO = 5,
    GOGO = 6,
};


// create statemachine
Statemachine testMachine;

// init state
statemachine.createNewState(SOURCE_STATE, "sourceState");
statemachine.createNewState(NEXT_STATE, "nextState");
statemachine.createNewState(CHILD_STATE, "childState");
statemachine.createNewState(TARGET_STATE, "targetState");

// build state-machine
statemachine.addChildState(NEXT_STATE, CHILD_STATE);
statemachine.setInitialChildState(NEXT_STATE, CHILD_STATE);

statemachine.addTransition(SOURCE_STATE, GO, NEXT_STATE);
statemachine.addTransition(NEXT_STATE, GOGO, TARGET_STATE);

// try to go to next state
bool success = testMachine.goToNextState(GO);
// success would be `true` in this case

// get curren state
const uint32_t stateId = statemachine.getCurrentStateId();
// stateId would be 4
const std::string stateName = statemachine.getCurrentStateName();
// stateName would be `nextState`

```

In the future there also should be triggered events after a state-change. Also failed states should be added ans so on.


### Common methods

This is really minimalistic at the moment, because here are only two methods now, but there will coming more.

#### string methods

Following functions are supported:

- split string at a specific character into a vector of strings 
- split them into a list of substring, where each substring has a maximum size
- replace a substring within a string

Example:

```cpp

#include <libKitsunemimiCommon/common_methods/string_methods.h>


std::string testString = "this is a test-string";

// split by a delimiter
std::vector<std::string> result1;
splitStringByDelimiter(result1, testString, ' ');
// the resulting list now contains ["this", "is", "a", "test-string"]

// split into max sizes
std::vector<std::string> result2;
result = splitStringByLength(result2, testString, 5);
// the resulting list now contains ["this ", "is a ", "test-", "strin", "g"]

// replace substring
std::string testString = "this is a test-string";
replaceSubstring(testString, "test", "bogus");
// variable teststring has not the content: "this is a bogus-string"

```

#### vector methods

Here is the only function for now to clear empty string from a vector of strings.

Example:

```cpp

#include <libKitsunemimiCommon/common_methods/vector_methods.h>


std::vector<std::string> testVector{"x","","y","z",""};

removeEmptyStrings(&testVector);

// after this testVector only contains ["x", "y", "z"]

```

## Code-Documentation

Documentation is buildable with doxygen:

```
doxygen Doxyfile
```

On Linux you need the packages `doxygen` and `graphviz`.


## Contributing

Please give me as many inputs as possible about bugs, bad code style, bad documentation and so on. 


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
