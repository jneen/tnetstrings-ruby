require 'rake/clean'

extconf = 'ext/extconf.rb'
makefile = 'ext/Makefile'
mod = 'ext/tnetstrings.so'
png = 'ext/viz.png'
src = Dir.glob('ext/*.[ch]')
src << makefile

CLEAN.include [ 'ext/*.o', png, mod ]
CLOBBER.include [ 'config.save', 'ext/mkmf.log', 'ext/extconf.h', png, makefile ]

file makefile => [extconf] do |t|
  Dir::chdir(File::dirname(extconf)) do
    unless sh "ruby #{File::basename(extconf)}"
      $stderr.puts "Failed to run extconf"
      break
    end
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
