# Term p
Little console text editor...  
  
### To make new command,
```D
1. Define command  : in `Command.hpp`
2. Add to command map   : in constructor of `CommandIntepreter`
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
- 12/6: change structure for command.   struct -> class
- 12/7: done?


# MEMO
- <s> Is it necessary to distinguish the type by argument of each command? e.g. I-Type, S-type, N-type
--> Maybe not.. The instructions use that strategy beacuse of hardware limitations. </s>   
-> 12/7 fixed 

- Template for function document
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

