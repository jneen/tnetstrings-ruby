require File.expand_path('../ext/tnetstrings', File.dirname(__FILE__))

module TNETS
  extend self
  extend TnetstringsCMethods
  include TnetstringsCMethods

  def load(str)
    c_parse(str)
  end
end
