ID:2264471    					      ID:2264547                                    
NAME:ORHAN 		  			          NAME:MUSTAFA
SURNAME:ALBAYRAK                      SURNAME:GÖNEN

We have 5 nodes which names are 's' for source  'r1' for router 1 'r2' for router 2 'r3' for router 3 'd' for destination.

Code Part has 3 files for experiment_1 in the "exp1" folder: "source.py" , "router-3.py" ,"destination.py" and input.txt
and 4 files for experiments "exp2" folder: " source.py"," r1.py", " r2.py" , " destination.py" and input.txt
For runnig experiment_1 exp1:
	Firstly destination.py have to be executed on d node:
	python3 destination.py
	Then r3.py  and source.py scripts have to be executed respectively:
	python3 router-3.py
	python3 source.py	
For runnig experiment_2 exp2:
	Firstly destination.py have to be executed on d node:
	python3 destination.py
python3  r1.py
python3  r2.py
Finally source.py script on s node needs to be executed:
	python3 source.py

You see that In the node s, you will see output.txt file which is the same as input.txt
You can check the equality of files with the following command:
---> diff output.txt input.txt



To make an interface down, use the following command:
--> ip link set dev <interface> down

To add packet loss to each link, following commands are executed at each node:
--> tc qdisc change dev [INTERFACE] root netem loss 5% delay 3ms 
--> tc qdisc change dev [INTERFACE] root netem loss 15% delay 3ms 
--> tc qdisc change dev [INTERFACE] root netem loss 38% delay 3ms
