# The Artificial Idiot
## Small Language Model (SLM)

This is a toy model of a language model, written in c++17. The program "trains" on a text file by counting the frequency at wich characters follow any particular k-gram. The program then generates text based on those transition probabilities.

### Compilation 
This repository provides a makefile for ease of compilation. Run
```bash
make
``` 
in terminal to compile program, and use

```bash
make clean
```
to remove compilation files.

### Usage

The program acts as a unix tool, and expects the following syntax:

```bash
./slm [-a alpha] k filename length
``` 
Arguments:
* k: Length of the k-grams. Must be a positive integer.
* filename: Path to the training textfile (relative to slm directory)
* length: Desired length of output text. Must be a positive integer greater than k.
* -a alpha: Optional pseudocount parameter. Must be positive. (default: 0)

Example usage:
```bash
./slm 3 someText.txt 50
./slm -a 0.01 6 here/be/some/text.txt 100
```

Generated text is printed to terminal. Without pseudoount smoothing, generation may stop early.

