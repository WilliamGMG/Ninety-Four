# 🧬 Ninety-Four 🧬

This is a program to compare the use of HashMap's and B-Tree's for structuring and searching multiple organisms genome sequences.

## **🔍 Where to get genome sequences**

1. Vist this [NCBI](https://www.ncbi.nlm.nih.gov/datasets/genome/) site.
2. In the search bar enter and find the organism whose genome you want to download.
3. After searching select an assembly underneath assembly.
4. Now select download and then download again.
5. Once the file is downloaded unzip it and locate a .fna file inside it.

## **📌 How To Use**

1. Clone the repository and compile the program with CMake.
2. Run the compiled executable.
3. The first step is to enter the paths to the .fna files you want to load.
   An example genome is included with the project and is located in `C:\Users\willi\ClionProjects\DSA\Ninety-Four\Example Genomes\E.Coli\ncbi_dataset\data\GCA_000005845.2\GCA_000005845.2_ASM584v2_genomic.fna`
4. Enter next to continue.
5. At this point the files will be loaded and you will be asked if you want to know which line(s) the sequence you searched for is on, enter yes or no.
6. Now you are able to input the sequence you want to search the file for. Note that the input sequences must be under the specified length and must not span multiple lines.
