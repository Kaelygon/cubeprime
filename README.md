https://oeis.org/A157026/b157026.txt
A157026 		Primes p with the property that p^3=a^3+b^3+c^3

---primeCube---
a,b,c>=0
p>2
a!=b!=c
a<b<c<p
p^3%9==(1 or 8)

primeCube [thread count] [current thread] [start] [end]
calculates every combination of n,m,k and checks if the cube root of the sum is a prime; up till [end] if [start]=0
Reads primes from file ./data/primes.bin, assuming it's sorted ascending and has primes up to 'ceil(sqrt([end]))+1'
if [start]==0, compute time increases approx by [end]^3/3
if these requirements are met, e.g. output will be
P^3		= P^3 expanded	=	a:[a] b:[b] c:[c]
19919^3 = 7903193128559 =  a:5462 b:11852 c:18247

example command to run the program for single thread, up to 911
./primeCube 0 0 0 911

12 threads up to 19919, skipping a<10000
for i in {0..11}
do
./primeCube 11 $i 10000 19919
done

---singlePrimeCube---
n,m,k>=0
p>2
n!=m!=k
singlePrimeCube [thread count] [current thread] [start] [P]
searches for a sum of three cubes that equals [P]^3 . [P] Doesn't necessarily need to be prime.
if [start]==0, compute time increases approx by [end]^2
Output current [a] when [a]%256==0
Outputs matches in same form as primeCube

When the programs finish they will output compute time in cpu time cycles, excluding initialization, and the number of found matches
e.g.
#took: 4594094
#found: 134


---writePrimes---
writePrimes [end] [1]
calculates primes to ./data/primes.bin up to 'ceil(sqrt([end]))+1'
if second argument is 1, file is reset before writing to the file
if the primes already exist in the file, calculates rest of the primes up to ceil(sqrt([end]))+1'

---bash scripts---
ghetto implementations for multithreading
primeCube: 			bashMultithread.sh
singlePrimeCube:	bashMultithreadSingle.sh

./datath/peak: greps for any found matches, least and most progressed core

Flaws of the program:
idk how to multithread
kinda jank but it sorta works