require './lib/tnetstrings/version'

Gem::Specification.new do |s|
  s.name = 'tnetstrings'
  s.version = TNETS.version

  s.authors = ["Jay Adkisson"]
  s.date = Time.now.getutc.strftime('%Y-%m-%d')

  s.description = <<-desc.strip
    A general-purpose tnetstrings library for Ruby
  desc

  s.summary = <<-sum
    A general-purpose tnetstrings library for Ruby
  sum

  s.email = %[jjmadkisson@gmail.com]
  s.files = Dir.glob('ext/**/*.{c,h,so}') + Dir.glob('lib/**/*.rb')

  s.homepage = 'https://github.com/jayferd/tnetstrings-ruby'
  s.require_paths = ['lib']

  s.test_files = Dir.glob('spec/**/*.rb')

  s.add_development_dependency('rspec', '~> 2.0')
  s.add_development_dependency('rake')
end

