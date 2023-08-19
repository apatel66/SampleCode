# SampleCode - Arjav Patel
Here are a few programs I wrote, which provide a small sample of my coding abilities. Click on each folder and the file(s) inside to view the code.

*NOTE: Much of the programs that I have written were projects for class and I cannot post it here since it would be an Honor Code violation. However I can share them privately in an interview upon request*
These projects include...
- Command line Euchre game with bots (C++) (EECS 280)
- Wheel of Fortune game w/ GUI (Java) (EECS 285)
- Spending tracker Android app (Java) (EECS 285)
- Instagram clone web-app (ReactJS, Python, SQL) (EECS 485)
- Search Engine with map reduce (Python) (EECS 485)
- Memory manager for operating systems (C++) (EECS 482)
- Network file system (C++) (EECS 482)
  
## Arduino
I also included a few programs I wrote as part of different research projects.
- `(Arduino) 2019ResearchCode` - In 2018-2019, I worked with Western Micigan University's Aersospace CubeSat Laboratory. The intent was to program an Arduino UNO micorcontroller to spin a reaction wheel at different speeds.
- `(Arduino) 2020ResearchCode` - In 2019-2020, I worked with Stryker engineers at StrykeForce Robotics. This program recieves telemetry data from a robot over UDP communication and displays it on the LCD screen for easy viewing. The type of data displayed is controlled by the robot's code in a seperate Java program. Unfortunately, this project was cut short due to Covid-19.
  
## C++
### USACO Training Problems
Series of 100 progressively difficult programming problems designed to improve individual coding proficiency and efficiency.
Visit the [USACO Training Page](http://usaco.org/index.php?page=training) for more information.

- `(C++) USACO Checker Challenge`
- `(C++) USACO Controlling Companies`
- `(C++) USACO Healthy Holsteins`
- `(C++) USACO Humble Numbers`
- `(C++) USACO Party Lamps`

### Try My Programs Out!
If you would like to try my USACO programs out, here is how you can run them on a Command Line Interface:

1. Scroll up and click the green "Clone or download" button on the right, then click "Download ZIP". This will download a folder called "SampleCode-master" into your downloads folder.
2. Open up a new command line and enter the following to change your directory into the "SampleCode" folder.
```
$ cd Downloads/SampleCode-master
```
3. Enter `ls` to view the various program folders.
4. Enter `cd` + the folder name to go into the folder. The folders with executable programs will all start with "USACO".
   (Tip: If you have typed enough characters, press `Tab` and the rest of the word will fill in - given you are in the right 
   directory)
5. Enter `ls` to view the files inside the folder. There will be one program, a sample input, and a text file containing the 
   output. For eaxmple, if I was in the `USACOChecker` folder, I would see `checker.cpp`, `checker.in`, and 
   `checkerOutput.txt`.
6. To compile the program, enter the following code. Remember, even though you can enter any word in place of "example", 
   "problemName" has to be the exact file name of the program.
```
$ g++ -o example problemName.cpp
```
7. Now to run the program, enter:
```
$ ./example
```
8. An output should appear. To compare what was printed with the real answers, enter this command:
```
$ open problemNameOutput.txt
```
9. This will open a text file of the correct answer. Check to see if my program works!

## Java
- `(Java) JavaRobotCode` - I have solved many of the USACO Training problems in Java as well, however, I included a sample program I wrote as practice for my FIRST FRC robotics team in 2019. Its purpose is to control a robot drive base with a joystick, similar to a Xbox controller.

## React / Javascript
- `(ReactJS) SkyscannerPriceViewer` - In order to get into Capital One's software engineering summit in 2021, I was tasked with building a flight price checker. I built it using React and the Skyscanner API. The user enters an origin, a destination, dates, and a currency, then the application with return a sorted list of flights in a table. The website also uses a color-blind friendly color pallate to improve accessibility. Here is the [GitHub repo]() and here is the [deployed webapp](). Please note, results might not show up since the API key may have expired.
- `(ReactJS) MarvinWebApp` - As part of EECS 449 (Conversational AIs), my group created a study AI chatbot called "Professor Marvin". Users upload a suite of PDFs to the chatbot, then once trained, users can interact with the chatbot like it's a personal tutor. Users can ask for summaries, Q/As, and vocab definitions. I built the front-end using React for the web-app which included a home, instruction, and about screens along with a drag-and-drop file upload and a chat interface.
