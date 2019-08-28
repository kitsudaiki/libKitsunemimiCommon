# libKitsuneCommon

## Description

This library contains some functions, I need for my other projects. There are functions for memory-handling, thread-handling, data representation and testing.

This is the first of my repositories that I made open-source. There will come much more, but this should be my first step.

### About my kitsune libraries

My first libraries hab really common names like libCommon and so on, but I thought this could be hard to find my code between other libraries, when my projects will become bigger. So I decided to make a common name over all my libraries, similar to the boost-libraries, for a better handling. I decided to use `Kitsune` as name for my projects, because Kitsunemimi are moe. ;)

### About my repositories in general

At the moment there are over 10 Kitsune-libraries an multiple tools in my private repos. I plan to make all open-source, but I have much to learn about open-source-projects. Most of all I have to improve my ticket-handling. So please help me to improve my workflow.

All my projects are mirrored to gitlab, where I have still my gitlab-ci runner. 

I don't really like it to write much comments into header-files. More exactly I absolutly hate it, when I have to search the provided functions of a header between a massive amount of comments. Header-files are for me primary to have an overview, of all provided functions, which I have see as fast as possible. Comments of functions, parameters and return-values in my code are only written into the source-file. So when something is unclear for a specific method, than look into the source-file. If the comment there are not helpful for you, then please write me a mail or an issue to fix this. 

## Content Overview

### Common items

These are classes for data-representation. At the moment there are data-items and table-items. The data-items were originally the core data handling structure inside libKitsuneJson for representing json-trees. Thats why the string output of these items still have json-format. The table-items are for table styled output of information. Internally it use the data-items.

### Data buffer

This is a simple buffer for binary-data. The primary advantage is the easier resizing when adding new data. Internally it uses alligned memory, because this is necessary for the direct read- and write-operations of the libKitsunePersistence.

### Threads

This class is only a collection of some thread-function like blocking and so on which I often use. This makes the creation of threads more easy for me. Additionally this class provides the ability to bind a new one of this thread to a specific cpu-thread (this feature is still a bit incomplete, because it has 4 threads as max number of threads).

### Tests

This is my very little test-framework. These are used for all unit-tests in all of my projects. Thats to macros it shows the exactly position in the failing test inside the code for easier debugging.

### Statemachine

It's only a simple statemachine in the moment. Basically its only to change the state and check the current state. It doesn't trigger any events after changing the state.

### Common methods

These contains some commonly used mehtods. At the moment there are only two, but there will come more.


## Build

### Requirements

paket | version
--- | ---
g++ | 6.3.0
qt5-qmake | 5.7.1

This are the version I have installed under Debian Stable via apt. Some older or newer version should work as well. I write my projects with the Qt-creator, but without Qt itself. Thats why qmake is required to build my projects.

IMPORTANT: All my projects are only tested on Linux. 

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.

Before running the build-script:

```bash
.
└── libKitsuneCommon
    ├── build.sh
    └── ...
```

After running the build-script:

```bash
.
├── build
│   └── libKitsuneCommon
│       ├── Makefile
│       ├── src
│       └── tests
├── libKitsuneCommon
│   ├── build.sh
│   └── ...
└── result
    ├── include
    │   └── libKitsuneCommon
    ├── libKitsuneCommon.so -> libKitsuneCommon.so.0.4.0
    ├── libKitsuneCommon.so.0 -> libKitsuneCommon.so.0.4.0
    ├── libKitsuneCommon.so.0.4 -> libKitsuneCommon.so.0.4.0
    └── libKitsuneCommon.so.0.4.0
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
- `DataObject`
	- This is a map-object for key-value-pair with a string as identifier and a DataItem-pointer as value
	- data can be added with the `insert`-method
- `DataArray`
	- It's a internally a vector of Dataitem-pointer
	- data can be added with the `append`-method

IMPORTANT: all getter here only return a pointer to the internal object. If you want a copy, you have to use the `copy`-method of the objects to recursivly the data-item-tree behind the pointer.

To see all offered possebilities, which are provided by the data-items, please see the header-file `common_items/data_items.h`. There is nearly all self-explaining, because there are basically only getter and setter. So the following is only a minimal example:

```cpp
#include <common_items/data_items.h>

// init some value
DataValue stringValue("test");
DataValue intValue(42);
DataValue floatValue(42.5f);

// init and fill array
DataArray array;
array.append(stringValue.copy());
array.append(intValue.copy());
array.append(floatValue.copy());

// init and fill object
DataObject object;
object.insert("asdf", stringValue.copy());
object.insert("hmm", intValue.copy());
object.insert("xyz", floatValue.copy());

// add the array also to the object
object.insert("array", array.copy());

int size = object.size();
// `size` is 4 (3 values and 1 array)


std::string output = object.print(true);
/**
`output` would look like this:

{
    "asdf": "test",
    "hmm": 42,
    "xyz": 42.500000,
    "array": [
        "test",
        42,
        42.500000
    ]
}
**/

std::string value = object.get("array")->get(2)->toValue()->toString();
// `value` would be `42.500000` as string
```

#### table-items

This is for printing informations as table on the commandline in form of this example:

```
+-----------------+---------+
| Name of column1 | column2 |
+-----------------+---------+
| this is a test  | k       |
| asdf            | hmmm    |
+-----------------+---------+
```

Its primary to print informations coming from a REST-API response in form a json. So it can be filled manually or with content which was parsed with libKitsuneJson (coming soon open-source).

- manual filling of the table:

```cpp
#include <common_items/table_item.h>


TableItem testItem;

// add columes
// first value is the internal used name to identify the values in the content.
// the second value is the name for the output. If this is not set, it uses the internal name here too.
testItem.addColumn("column1", "Name of column1");
testItem.addColumn("column2");

testItem.addRow(std::vector<std::string>{"this is a test", "k"});
testItem.addRow(std::vector<std::string>{"asdf", "qwert"});

// convert to string
std::string output = testItem.print();
/**
here ouput has nwo the content: 

"+-----------------+---------+\n"
"| Name of column1 | column2 |\n"
"+-----------------+---------+\n"
"| this is a test  | k       |\n"
"| asdf            | hmmm    |\n"
"+-----------------+---------+\n";
**/

```

- fill with predefined informations:

```cpp
#include <common_items/table_item.h>

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

std::string output = testItem.print();
/**
here ouput has nwo the content: 

"+-----------------+---------+\n"
"| Name of column1 | column2 |\n"
"+-----------------+---------+\n"
"| this is a test  | k       |\n"
"| asdf            | hmmm    |\n"
"+-----------------+---------+\n";
**/

```

### Data buffer

The data-buffer is only a struct with some external functions for easier byte-buffer-handling. The internal byte-array is a alligned memory with a size of a multiple of the defined block-size. This is necessary for direct read- and write-operations to the storage. Beside this, the struct contains the current size of the buffer in number of bytes and number of allocated blocks. It is possible to use the `data` as mormal byte-array for read and write operations or use the `addData` and `getBlock` for access. The `addData` allocates automatically the required number of block, if the buffer is not big enough. 

```cpp
#include <buffering/data_buffer.h>

// initialize new data-buffer with 10 x 4KiB
DataBuffer testBuffer(10);

int value = 42;

// write data to buffer a the position pointed by the value `testBuffer.bufferPosition`
// you can set the bufferPosition directly to write at a custom location
// or write your data directly with memcpy to any position of `testBuffer.data`
bool success = testBuffer.addData(&value);

// This example is a bit stupid, because it is the fist value in the data-buffer
// It get the block with id 0 from the buffer as int-array and from with it gets the first element
int readValue = static_cast<int>(testBuffer.getBlock(0))[0];

// clear buffer and reset to only one allocated block
testBuffer.reset();

```

For more control you can also use the data-methods directly:

```cpp
#include <buffering/data_buffer.h>

// initialize new data-buffer with 10 x 4KiB
DataBuffer testBuffer(10);

int value = 42;

// write data to buffer a the position pointed by the value `testBuffer.bufferPosition`
bool success = addDataToBuffer(&testBuffer, static_cast<void*>(value), sizeof(int);

// additional allocate 10 more block
success = allocateBlocks(&testBuffer, 10);

// clear the buffer and reduce it to 10 block again
success = resetBuffer(&testBuffer, 10);

```

### Threads

The usage can be explained with the following examples:

- This is the basic look of a new class, which should run in a separate thread:

```cpp
// demo_thead.h

#include <threading/thread.h>


class DemoThread 
    : public Kitsune::Common::Thread
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
#include <demo_thead.h>

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

### Tests

For using the unit-tests your test-class have to inherit the class `Kitsune::Common::UnitTest` and give the header fo the constructur a name for the test as string. Inside the single tests you can than call the two macros `UNITTEST(<VARIABLE_TO_CHECK> , <EXPECTED_VALUE);` and `UNITTEST_NEG(<VARIABLE_TO_CHECK> , <NOT_EXPECTED_VALUE);`. First is successful when equal and second one is successful, when unequal. 

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

#include <testing/unit_test.h>

class Demo_Test 
    : public Kitsune::Common::UnitTest    // <-- connect with unit-tests
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
    : Kitsune::Common::UnitTest("Demo_Test")    // <-- give the unit-test a name
{
    some_test();	// <-- call the test-method
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
    UNITTEST(answerForAll, 42); 	// <-- single test

    // inverted test
    UNITTEST_NEG(answerForAll, 0);
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

#include <statemachine/statemachine.h>


// create statemachine
Statemachine testMachine;

// add states
testMachine.createNewState("sourceState");
testMachine.createNewState("nextState");

// add transitions
testMachine.addTransition("sourceState", "go", "nextState");

// try to go to next state
bool success = testMachine.goToNextState("go");
// success would be `true` in this case

// get curren state
std::string state = statemachine.getCurrentState();
// state would be `nextState`

```

In the future there also should be triggered events after a state-change. Also failed states should be added ans so on.


### Common methods

This is really minimalistic at the moment, because here are only two methods now, but there will coming more.

#### string methods

The only function hier is the ability to split string at a specific character into a vector of strings.

Example:

```cpp

#include <common_methods/string_methods.h>


std::string testString = "this is a test-string";

// run task
std::vector<std::string> result = splitString(testString, ' ');

// the resulting result now contains ["this", "is", "a", "test-string"]

```

#### vector methods

Here is the only function for now to clear empty string from a vector of strings.

Example:

```cpp

#include <common_methods/vector_methods.h>


std::vector<std::string> testVector{"x","","y","z",""};

removeEmptyStrings(&testVector);

// after this testVector only contains ["x", "y", "z"]

```


## Contributing

Please give me as many inputs as possible about bugs, bad code style, bad documentation and so on. 


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details