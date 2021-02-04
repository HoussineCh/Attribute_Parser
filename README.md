# Attribute_Parser
html like attribute parser implemented with c++.

- The program takes N lines of html code, followed by Q lines of querries.

- Each querry prints the value of the requested attribute.

- If the requested attribute or tag doesn't exist, or the sequence of nested tags is wrong, the querry prints "Not Found"

Example input and output:
''
Input:
10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size

Output:
GoodVal
Not Found!
10
BadVal
Not Found!
auto
Not Found!
2
Not Found!
3
''
