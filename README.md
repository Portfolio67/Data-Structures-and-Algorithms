# Data-Structures-and-Algorithms

<!doctype html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Data Structures</title>
</head>
<body>
<div class="TOC">
<ul>
<li><a href="#data-structures">Data Structures</a>

<ul>
<li><a href="#vectors"><strong>Vectors</strong></a></li>
<li><a href="#hash-tables"><strong>Hash tables</strong></a>

<ul>
<li><a href="#tree-structures">Tree structures</a></li>
<li><a href="#hashchainin">Hash/Chainin</a></li>
</ul></li>
<li><a href="#references">References</a></li>
</ul></li>
</ul>
</div>

<h1 id="data-structures">Data Structures</h1>

<p>Times to load and to sort, (after removed all un-needed prints)
vectorSorting program with title search, quicksort, selection, partition algorithms, </p>

<p>| 17937 bids | Organized data | Unorganized data |
|:--|:--|:--|
| Loading time into vector. | 0.46459 sec |0.460508 sec |
| Selection Sort | 21.5915 sec | 21.7899 sec |
| Quick Sort with partition | 0.064843 sec| 0.054884 sec|
 <img src="" alt="" />
 <a href="https://github.com/Portfolio67/Data-Structures-and-Algorithms/blob/e621387f26f5d8a2f8006036cbae61f910479d1c/img/Screen%20Shot%202022-10-05%20at%203.12.15%20PM.png"></a></p>

<h2 id="vectors"><strong>Vectors</strong></h2>

<p>Vector are typically used over arrays because there more versatile and stable than arrays.<br/>
All programs except linkedList, made use of a vector to load the bids header, from the csv file then print it. The vectorSorting, and the HashTable made use of the vector in different ways.
The Hash table used vector to hold nodes (buckets of data) not pointers to nodes, like a linked list. During the final stage of searching the hash the program walks down the vector, to match the bidId in the hash bucket. &amp;(<a class="autolink" href="https://nodes.at">nodes.at</a>(key)) look for the old node using the Node at function, by giving it the key or index into the vector. the pointer just gives us the value. The address is &amp;(address of operator) The search finds the first one in the vector.<br/>
The VectorSorting program uses a vector data structure to hold a collection of bids, that is passed to the algorithms. Then in the partition algorithm that quick sort uses the program swaps the low and high bids using built-in vector methods sorting the whole list. Using partition with a mid point keeps splitting it down until just two elements are compared for the left and right side.</p>

<p>The best use of the vector is the vectorSorting program, it loads all the data that is unorganized or organized into the vector with a call to a function. The problem here is to take 17937, and 179 bids and get them organized in alphabetical order in a linear list the fastest. It is using the title to sort an organized list.</p>

<h2 id="hash-tables"><strong>Hash tables</strong></h2>

<h3 id="tree-structures">Tree structures</h3>

<p>Algorithms
Search / Sort
The VectorSorting.cpp program starts with a struct to hold the bids and uses just a vector with two optional sort algorithms: selection Sort and quick Sort; the quick sort needs a partition algorithm to work.</p>

<h3 id="hashchainin">Hash/Chainin</h3>

<p>The HashTable.cpp program starts with a struct to hold the bids and is the only program in
Choice of data structures and algorithms
Overall effectiveness
Programmers’ abilities
Modularity &amp; Reusable
The programs: HashTable, BinarySearchTree, linkedList, used Scope resolution operator, in C++ it is the ::<br/>
This can be used for a couple things, but in this case it allowed to define a function outside a class. (geeksforgeeks) This gave the program modularity. It was easy to read, reuse and debug. </p>

<p>Annotation
Conclusion
The importance of data structures
The role and importance of algorithms
The lessons learned</p>

<h2 id="references">References</h2>

<p>Know Thy Complexities! <a class="autolink" href="https://www.bigocheatsheet.com">https://www.bigocheatsheet.com</a></p>

<p>Lysecky, L. Vahid F. (August 2017 ). Data Structures Essentials With C++
Retrieved from URL. <a class="autolink" href="https://learn.zybooks.com/zybook/SNHUCS260v2/chapter/3/section/1/">https://learn.zybooks.com/zybook/SNHUCS260v2/chapter/3/section/1/</a></p>

<p><a class="autolink" href="https://cppreference.com">cppreference.com</a></p>

<p>Scope resolution operator in C++. <a class="autolink" href="https://www.geeksforgeeks.org/scope-resolution-operator-in-c/">https://www.geeksforgeeks.org/scope-resolution-operator-in-c/</a></p>
</body>
</html>
