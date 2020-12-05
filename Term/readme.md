# Term p
Little console text editor...  
  
### To make new command,
```D
1. Define command type  : `CommandType` in `CommandIntepreter.hpp`
2. Define verification  : `is_valid_cargs()` in `CommandIntepreter.hpp`
3. Add to command map   : `cmd_map` with arguments type (e.g. I_TYPE) in `CommandIntepreter.hpp`
4. Define action        : `execute_command()` in `main.cpp`
```

# TODO
### Implementation
- dk gkrl tlfgdj
### Design pattern
- ***Startegy*** for dynamic width/hegiht?
- ***Factory***
- ***Singleton***

### Exception handling
- <s>Input: `n gre`</s>
- <s>Input: `i(1,2,wo)`</s>
- <s>Input: `d(1,)`</s>
- <s>Input: `d(0,0)`</s>
- <s>Input: `d(1,55)`</s>
- <s>Input: `i(1,10,hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohello)`</s>
- <s>Input: d(1,1)</s>
- <s>Input: d(1,2)</s>
- <s>Input: i(0,1,0)</s>
- <s>Input: i(1,1,30)</s>
- TODOTODO..

### Validation
- Line invariant

# Log
- 12/3: make&execute ok
- 12/4: ...
- 12/6: OK..? except design pattern?


# MEMO
Template for function document
```C++
/** 
 * Function description
 * 
 * @param param1 param1 description
 * @return return value description
 * @example
 *           before      buf:_____  ,  of:~
 *           after       buf:_____  ,  of:~
 * @invariant
 *          #pre_condition => #post_condition (TODO)
 * */
```

