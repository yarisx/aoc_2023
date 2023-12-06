import math

# Today's assignment does not even deserve a separate program
# since effort for parsing input would be way more
# than effort to actually solve the task
# Below is the formula, feel free to wrap it into a program template of your liking
def calc(T, D):
    mi = math.floor((T - math.sqrt(T*T - 4*D))/2) + 1
    ma = math.ceil((T + math.sqrt(T*T - 4*D))/2) - 1
    ways = ma - mi + 1
