
name = input()

loc = name.find('-')

if loc == -1:
    print("NO")
    exit()

ins = name[:loc]
team = name[loc+1:]

if 1 < len(ins) <= 8:
    if 1 <= len(team) <= 24:
        print("YES")
        exit()

print("NO")