s= input("Enter the grammar:")
# grammar format S->Sab/xy
if s[0]!=s[3]:
    print("No left recursion")
if s[0]==s[3]:
    x=s[0]
    l=len(s)
    a=''
    c=''
    b=s[0]+"'"
    #print(b)
    for i in range(l):
        if s[i]=="/":
            a=a+s[i+1:]
    for i in range(l):
        if s[i]=="/":
            c=c+s[4:i]
    a=a+b
    c=c+b
    print(s[0],"->",a)
