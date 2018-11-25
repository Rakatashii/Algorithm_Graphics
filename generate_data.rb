#!/usr/bin/env ruby

require 'Faker'

def is_numeric?(obj)
   obj.to_s.match(/\A[+-]?\d+?(\.\d+)?\Z/) == nil ? false : true
end

n = 200

args = ARGV;
argc = ARGV.size
if (argc >= 1 && is_numeric?(args[0]))
    n = args[0].to_i
end

dir = "/Users/christianmeyer/cpp/ch11/P11_14_15_16/"
file = "/Users/christianmeyer/cpp/ch11/P11_14_15_16/data.txt"
if (argc >= 2)
    file = dir + args[1].to_s
end

separate = "|";
endline = "\n";
#line length = 20 + 10 + 2 (+2 for pipe and newline chars)
File.open(file, 'w') {|f|
    printline = ""
    Faker::Config.random.seed
    f.write(n, endline);
    n.times do
        p1 = rand();
        p2 = rand();
        x = 1 + rand(1000);
        if (p1 >= 0.5)
            x *= -1
        end
        y = 1 + rand(1000);
        if (p2 >= 0.5)
            y *= -1
        end
        f.write(x, separate, y, endline)
    end

}
