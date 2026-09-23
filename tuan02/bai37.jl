function main()
    n = parse(Int, readline())
    arr = parse.(Int, split(readline()))
    
    chan = le = am = 0
    
    for x in arr
        if x < 0
            am += 1
        end
        
        # Trong Julia co the dung x % 2 != 0 hoac rem(x, 2) != 0
        if x % 2 != 0
            le += 1
        else
            chan += 1
        end
    end
    
    println("chẵn $chan, lẻ $le, âm $am")
end

main()