[Microsoft Windows Version]
1. Extract this archive to a folder.
2. For Single Threaded version, go to the '01_SingleThread' folder and click on 'SingleThreadGoL.exe'
3. For Multi Threaded version, go to the '02_MultiThread' folder and click on 'MultiThreadGoL.exe'
3. For Interactive version, go to the '03_Interactive' folder and click on 'InteractiveGoL.exe'
4. To see previous results, go to the '04_View_Results' folder and click on 'GoL_Launcher.exe'

** The 'Source_Code' folder contains all the source code files of our project. **

[Linux Version]
1. Extract this archive to a directory.
2. For Single Threaded version, change your directory to the 'Source_Code/Linux_Version/01_SingleThread/' folder using the following command:
	$ cd Source_Code/Linux_Version/01_SingleThread/
3. Run the following commands:
	$ ccmake .
	$ make
4. Run the program using the following command:
	$ ./GameOfLife
5. For the Multi Threaded and Interactive versions, change the step 2 command to:
	$ cd Source_Code/Linux_Version/02_MultiThread/
		--- OR ---
	$ cd Source_Code/Linux_Version/03_Interactive/
6. The rest commands will remain the same.

