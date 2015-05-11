I have fully completed project 5 in my client_final.c.

-Usage: ./client_final.c <ip 1> <port 1> <ip 2> <port 2>.....  

-Will accept any number of servers
-Will read in any size file up to 512,000b 
-Creates one thread per server
-Threads then read in packets from their servers until they stop recieving data and then they all terminate
-I stored all packets in a global char * packets[].
-No memory leaks :D  