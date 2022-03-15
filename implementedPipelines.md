# Pipeline
### Generators

##### Value generators
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| Sensor | Creates a generator from a sensor | <nobr>polling rate: Num</nobr><br><nobr>Args...: [Key, Arg] </nobr><br> | | [Val] | :black_square_button: |  
| File  | Takes a file pointer, iterates throught the values in the file | FILE* | | [Num] [Char] | :black_square_button: |
| Value generator | Repeats a value | Value to repeat | value |  | :black_square_button: |
| Sine generator | Generates a sine wave | <nobr>Amp: Num</nobr><br><nobr>Freq: Num</nobr><br><nobr>Phase: Num</nobr> | | [Num] | :black_square_button: |

##### Value modifiers
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | :-------- | ----- | ------ | ---- |
| Random error | Interts error into data at random intervals | <nobr>chance: Num</nobr><br><nobr>chance: Num</nobr><br>  | a | b | :black_square_button: |
| Noisy | Creates noise byt adding to or subracting some value from the inserted value |  | a | b | :black_square_button: |

### Pipeline pieces

##### Stateful

| Name 	| Function | argument<br><nobr>all: (state: State)</nobr><br> | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| transformM | applies function to value, can change state | <nobr>function: (Val -> Val)</nobr><br> | Val | Val |
| max | finds and updates the max value so far | | [Num] Num | Num | :black_square_button: |
| min | finds and updates the min value so far | | [Num] Num | Num | :black_square_button:|
| standardDeviation | get the standard deviation | 
| running average | find the running average of the last X values |  |

##### Stateless
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| transform | applies a function to a values in the pipeline | <nobr>function: (Val -> Val)</nobr><br> | Val | Val | :ballot_box_with_check: | 
| Chunk | Split input in chunks of size N | <nobr>N: Num</nobr> | [Val] | [[Val]] | :black_square_button: |
| Concat | flattens list | | [[Val]] | [Val] | :black_square_button: |

### Message formatter

| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| MQTT formatter | Takes arguments and formats them according to the specified format | Format: [Key, Val] | [Val] | MQTT:JSON | :black_square_button: |

### Sink
| Name 	| Function | argument | Input | Output | Impl |
| -----	| -------- | -------- | ----- | ------ | ---: |
| MQTT send | Sends the MQTT:JSON messsage | destination | MQTT:JSON | | :black_square_button: |


# State
### Initial state
### Prior knowlege
### "Learned" State