using Printf

function main()
    n = parse(Int, readline())
    nums = parse.(Int, split(readline()))

    tong = nums[1]
    min_val = nums[1]
    max_val = nums[1]

    @inbounds for i in 2:n
        x = nums[i]
        tong += x
        if x < min_val
            min_val = x
        end
        if x > max_val
            max_val = x
        end
    end

    avg = tong / n   # Julia: / đã là chia thực
    @printf("%d %.4f %d %d\n", tong, avg, min_val, max_val)
end

main()