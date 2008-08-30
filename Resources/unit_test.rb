#!/usr/bin/ruby

$headers = ["<anidb.h>", "<stdio.h>", "<stdlib.h>", "\"test.h\""]
$main = "#{ARGV[0]}/main.c"
$test_file_expr = /^test_.*\.c$/
$test_func_expr = /test_.*\(void\)\W+$/
$setup_expr = /test_.*_setup\(.*/ 
$teardown_expr = /test_.*_teardown\(.*/

def usage
  puts "#{$0} <directory>"
  exit 1
end

def filter_function(f)
  return f.gsub(/(int|void(\ )?|\n)/, "")
end

def add_prototype(f, s)
    ss = s.sub("()", "(void)")
    if s =~ $setup_expr
      f << "int #{ss};\n" 
    else
      f << "void #{ss};\n"
    end
end

def add_setup(f, s)
  f << "(void)fprintf(stderr,\"Setting up:#{s}\\n\");\nif (0 ==#{s})\n{\n"
end

def add_teardown(f, t)
  f << "(void)fprintf(stderr,\"Tearing down:#{t}\\n\");\n#{t};\n}\n"
end

def add_function(f, m)
  f << "(void)fprintf(stderr,\"Testing #{m}\\n\");\n#{m};\n"
end

def get_setup(f)
  File.new(f).each { |l| return filter_function(l) if l =~ $setup_expr }
  return nil
end

def get_teardown(f)
  File.new(f).each { |l| return filter_function(l) if l =~ $teardown_expr }
  return nil
end

usage unless ARGV.length == 1 and File.directory?(ARGV[0])
File.delete($main) if File.exists?($main)
File.open($main, "w") { |main| 
  $headers.each { |h| main << "#include #{h}\n" }
  main << "\nint errors = 0;\n\n"
  main << "char error_names[1024][128];\n"
  # build a list of all available functions and use them as prototypes
  Dir.foreach(ARGV[0]) { |f|
    next unless f =~ $test_file_expr
    file = "#{ARGV[0]}/#{f}"
    File.new(file, "r").each { |l|
      add_prototype(main, filter_function(l)) if l =~ $test_func_expr
    }
  }
  main << "\nint main(int argc, char **argv)\n{\nint i = 0;\n"
  # again, walk through all files but this time check for setup and teardown
  # and embed the test-functions
  Dir.foreach(ARGV[0]) { |f|
    next unless f =~ $test_file_expr
    file = "#{ARGV[0]}/#{f}"
    ifdef_file = f.sub(/\./, "_").tr("a-z", "A-Z")
    main << "\n#ifdef #{ifdef_file}\n"
    main << "#if #{ifdef_file} == 1\n"
    setup, teardown = get_setup(file), get_teardown(file)
    add_setup(main, setup) unless setup == nil
    File.new(file, "r").each { |l|
      if l =~ $test_func_expr and not l =~ $setup_expr and not l =~ $teardown_expr
        add_function(main, filter_function(l))
      end
    }
    add_teardown(main, teardown) unless teardown == nil
    main << "#endif /* #{ifdef_file} == 1 */\n"
    main << "#endif /* #{ifdef_file} */\n\n"
  }
  main << "(void)fprintf(stderr,\"================================\\n\");\n"
  main << "if (errors > 0)\n{\n"
  main << "(void)fprintf(stderr,\"%d Errors occured in: \", errors);\n"
  main << "for (i = 0; i < errors; i++)\n{\n(void)fprintf(stderr, \"%s, \", error_names[i]);\n}\n"
  main << "(void)fprintf(stderr,\"\\n\");\n}\n"
  main << "else\n{\n(void)fprintf(stderr,\"No errors occured.\\n\");\n}\n"
  main << "return 0 == errors ? EXIT_SUCCESS : EXIT_FAILURE;\n}\n"
}
