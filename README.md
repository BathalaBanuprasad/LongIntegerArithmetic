# LongIntegerArithmetic

# OVERVIEW:
In this program, i am considering two operators ADD('+') and MUL('*')
Performing infix evalutaion on these, based on operator precedence between the two operators.
To perform, infix evaluation i had to use STACKS to store operators and operands. 
And by checking operator presedence, i am evalutaing the given expression.

# IMPLEMENTATION:
Implemented two types of stacks to store operator and operands. And implemented necessary functions of a stack.
Using a single Linked list to store all, operators and its result
Addition implementation is similiar to a FULL ADDER in digital circuits. Each addition is performed using 4 digits of two operands and carry of previous addition. Then storing the sum and carry, and updating the result.
Multiplication implementation is similiar to convolution (As i studied in my signals and systems course of my UG). It is just reversing blocks (4 digits of operand) of one number. Perform subsequent shifting, multiplication and addition of blocks until no overlapping blocks are present.
Used an infix evaluation algorithm to evaluate the given expression.
While printing the output, converting the number to corresponding string to print 0's in Most significant bits as well. (Printing "0001" instead of just 1)

# SAMPLE INPUTS AND OUTPUTS:
only + and * is supported
Number representation: xxxx,xxxx$*xxxx,xxxx$=Result
No spaces between operands, operator and equal.

1.	Input: 1110,0000$*0011$+0009$
	Output: 0001,2210,0009

2.	Input: 1120,2560$*8597,6214,7811$+1234,5678,9100$=
	Output: 0963,1537,1700,3838,5260

3.	Input: 1234,5678,9100$+1120,2560$*8597,6214,7811$=
	Output: 0963,1537,1700,3838,5260

4.	Input: 0001$*0000$=
	Output: 0000

5.	Input: 1111,2222,6666,7777,8888$+1234,5678,4231$=
	Output: 1111,2222,7901,3456,3209
