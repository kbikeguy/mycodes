### CSC-372 Analysis of Algorithms, Fall 2020   
**Project 5:** Strongly Connected Components for Social Networks      
**Authors:** Riley Campbell, Lane Moseley   

---

**Usage:**
* If a Python virtual environment is needed:
    * Create the virtual environment:
        * ```python3 -m venv venv```
    * Activate the virtual environment:
        * ```source venv/bin/activate```  
* Install the Python dependencies:
    * ```pip3 install -r requirements.txt```
* Run the program:
    * ```python3 main.py``` 
    * The program will ask for a file of names. These files are stored in the ```/data``` directory.
        * Example input: ```data/5names.txt```
    * The program will create random connections between the people listed in the file and display a graph of the strongly connected components.
* Run the tests:
    * ```python3 test_main.py```
