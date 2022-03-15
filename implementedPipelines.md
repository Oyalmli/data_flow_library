# Pipeline
### Generators

##### Value generators
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| Sensor | Creates a generator from a sensor | <nobr>polling rate: Num</nobr><br><nobr>Args...: [Key, Arg] </nobr><br> | | [Val] | :white_large_square: |  
| File  | Takes a file pointer, iterates throught the values in the file | FILE* | | [Num] [Char] | :white_large_square: |
| Value generator | Repeats a value | Value to repeat | value |  | :white_large_square: |
| Sine generator | Generates a sine wave | <nobr>Amp: Num</nobr><br><nobr>Freq: Num</nobr><br><nobr>Phase: Num</nobr> | | [Num] | :white_large_square: |

##### Value modifiers
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | :-------- | ----- | ------ | ---- |
| Random error | Interts error into data at random intervals | <nobr>chance: Num</nobr><br><nobr>chance: Num</nobr><br>  | a | b | :white_large_square: |
| Noisy | Creates noise byt adding to or subracting some value from the inserted value |  | a | b | :white_large_square: |

### Pipeline pieces

##### Stateful

| Name 	| Function | argument<br><nobr>all: (state: State)</nobr><br> | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| transformM | applies function to value, can change state | <nobr>function: (Val -> Val)</nobr><br> | Val | Val |
| max | finds and updates the max value so far | | [Num] Num | Num | :white_large_square: |
| min | finds and updates the min value so far | | [Num] Num | Num | :white_large_square:|
| standardDeviation | get the standard deviation | 
| running average | find the running average of the last X values |  |

##### Stateless
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| transform | applies a function to a values in the pipeline | <nobr>function: (Val -> Val)</nobr><br> | Val | Val | :white_check_box: | 
| Chunk | Split input in chunks of size N | <nobr>N: Num</nobr> | [Val] | [[Val]] | :white_large_square: |
| Concat | flattens list | | [[Val]] | [Val] | :white_large_square: |

### Message formatter

| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| MQTT formatter | Takes arguments and formats them according to the specified format | Format: [Key, Val] | [Val] | MQTT:JSON | :white_large_square: |

### Sink
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| MQTT send | Sends the MQTT:JSON messsage | destination | MQTT:JSON | | :white_large_square: |


# State
### Initial state
### Prior knowlege
### "Learned" State