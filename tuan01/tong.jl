n = parse(Int, readline())

a = parse.(Int, split(readline()))

total = sum(a)
max_value = maximum(a)

println(total, " ", max_value)
