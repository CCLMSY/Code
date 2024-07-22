import re
import re

T = int(input())

for _ in range(T):
    url = input()
    protocol, location, *path = re.split(r"://|/", url)
    variables = [p for p in path if "=" in p]
    print(protocol)
    print(location)
    for variable in variables:
        print(variable)