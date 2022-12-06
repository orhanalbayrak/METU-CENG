ID:2264471    					      ID:2264547                                    
NAME:ORHAN 		  			      NAME:MUSTAFA
SURNAME:ALBAYRAK                                      SURNAME:GÖNEN


We have 5 nodes which names are 's' for 'r1' for router 1 'r2' for router 2 'r3' for router 3 'd' for destination.

Code Part has 5 files for discovering in the "discoveryScripts" folder: "s.py" , "r1.py" , "r2.py", "r3.py" , "d.py"
and 3 files for experiments "experimentScripts" folder: "exp_s.py" , "exp_r3.py" , "exp_d.py"


First of all, scripts in the "src folder" needs to be deployed to their proper nodes on the network.

Then on each node: "chmod +x <script_name>" command needs to be executed to make the script executable by user.

To do this:
Download the configureR1.sh from <<<< https://odtuclass.metu.edu.tr/pluginfile.php/257424/mod_assign/intro/configureR1.sh  >>>> then write :
root@root:~$ chmod +x configureR1.sh
root@root:~$ ./configureR1.sh
after that downdload configureR2.sh from <<<< https://odtuclass.metu.edu.tr/pluginfile.php/257424/mod_assign/intro/configureR2.sh?time=1571568620305 >>>> then write :
root@root:~$ chmod +x configureR2.sh
root@root:~$ ./configureR2.sh



Then to initiate sending process for discoveryScripts:

	Firstly d.py have to be executed on d node:
	python3 d.py
	
	Then r2.py, r1.py, r3.py  and d.py scripts have to be executed on r2, r1, r3 and d nodes respectively:
	python3 r2.py
	python3 r1.py
	python3 r3.py
	


	Finally s.py script on s node needs to be executed:
	python3 s.py

For runnig experiment experimentScripts:

	Firstly exp_d.py have to be executed on d node:
	python3 exp_d.py
	
	Then  exp_p3.py  and have to be executed r3 node:

	python3 exp_r3.py
	


	Finally s.py script on s node needs to be executed:
	python3 s.py



 
	To access the measured cost of links[r1(s-r1,r1-r2,r1-d),r2(s-r2,r2-d),r3(s-r3,r3-r2,r3-d)] saved in the link_costs.txt  file for each node with same name write that in the r1,r2,r3 nodes' terminal:
root@root:~$  cat link_costs.txt 
	
	To access the end_to_end delay file:
root@root:~$  cat end_2_end.txt 
	
	After this final execution; 

To show network delay for a node following command has been used:
	tc qdisc show dev [INTERFACE]

To delete network delay for a node following command has been used:
	tc qdisc del dev [INTERFACE] root

To add network delay for experiment following commands has been used:

	tc qdisc add dev [INTERFACE] root netem delay 20ms 5ms distribution normal
	tc qdisc add dev [INTERFACE] root netem delay 40ms 5ms distribution normal
	tc qdisc add dev [INTERFACE] root netem delay 50ms 5ms distribution normal

