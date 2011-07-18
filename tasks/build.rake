require 'rake/clean'

extconf = 'ext/extconf.rb'
makefile = 'ext/Makefile'
ragel = 'ext/tnetstrings.c.rl'
ragel_out = 'ext/tnetstrings.c'
mod = 'ext/tnetstrings.so'
png = 'ext/viz.png'
src = Dir.glob('ext/*.c')
src << makefile

CLEAN.include [ 'ext/*.o', png, mod ]
CLOBBER.include [ 'config.save', 'ext/mkmf.log', 'ext/extconf.h', png, makefile ]

file ragel_out => ragel do
  unless sh "ragel -C #{ragel} -o #{ragel_out} -G0"
    $stderr.puts "failed to run ragel"
    break
  end
end

file makefile => [extconf, ragel_out] do |t|
  Dir::chdir(File::dirname(extconf)) do
    unless sh "ruby #{File::basename(extconf)}"
      $stderr.puts "Failed to run extconf"
      break
    end
  end
end

file png => ragel do
  unless sh "ragel -V #{ragel} | dot -Tpng > #{png}"
    $stderr.puts "failed to generate the image"
    break
  end
end

file mod => src do |t|
  Dir::chdir(File::dirname(extconf)) do
    unless sh "make"
      $stderr.puts "make failed"
      break
    end
  end
end

desc "Build the native library"
task :build => mod

task :viz => png do
  viewer = ENV['viewer'] || 'eog'
  sh "#{viewer} #{png}"
end
