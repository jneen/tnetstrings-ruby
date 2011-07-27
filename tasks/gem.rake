namespace :gem do
  task :package => [:build] do
    sh 'gem build tnetstrings.gemspec'
  end

  task :publish => :package do
    require './lib/tnetstrings/version'
    sh "gem push tnetstrings-#{TNETS.version}.gem"
  end
end
