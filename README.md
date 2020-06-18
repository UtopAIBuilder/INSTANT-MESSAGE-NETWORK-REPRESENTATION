# INSTANT-MESSAGE-NETWORK-REPRESENTATION (Implemented in C-language)
Problem Statement: We very well know that there are many real life problems that can be reduced to graph problems, whether it be finding suitable topology for a particular communication system(routing problem) or shortest route between a source and a destination (eg. Google maps). In this particular application we want to represent an instant message network representation which is changing dynamically based on communication between two users at a particular time instant. This represntation can then be used for behavioural study of pattern of communication between any two users or even a cluster with respect to time.

Proposed Solution :

1) Reduction of above problem using Time Varying Graph: A user will be mapped to a vertice with it’s label being the unique ID of the user. An edge will represent an ongoing converstation between two users at a particular time instant( undirected unweighted edge because the communcation is supposed to be two way).

2) Storage of time varying graphs: It won’t be a feasible solution to create new graph every time a connection is made or disconnected as we might have to create copies of even an unchanged large part of the graph. Hence I will be using partially persistent graph data structure to model this problem. There is no persitent data structures in C language hence this whole work will be done from scratch. For the sake of convenience we are assuming the no. of users during the whole experiment remains constant say n. Our time varying graph will be represented using adjecency list (with the partially persistent property).

3) Operations invoved:

initGraph(Graph g): a sparse random graph will be generated using erdos reny model of random graph generator (version v_0).

new_conversation(i,j) : a new edge will be added between vertices i and j and a new version of graph will be created. And prints error if edge already exists.

end_conversation(i,j): an edge between vertices i,j will be removed from the graph if it exists and a new version of graph will be created; else an error will be printed.

degree(i,ver): this will return degree of i in version ver (which is basically no. Of users,user i is communicating with ,in version ver).

4) Demonstration:

10 times new_conversation(i,j) will be called with random i,j (making sure i,j don’t already have an edge between them)

10 times end_conversation(i,j) will be called with random i,j (making sure i,j have an edge between them).

.Then space comparision will be done with respect to non persistent (snapshot approached) graph and our partially persitent graph.

. Plots showing variation of deg of i with respect to version will be presenteted.
