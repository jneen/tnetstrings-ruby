require File.expand_path('../ext/tnetstrings', File.dirname(__FILE__))

module TNETS
  extend self

  def load(str)
    c_parse(str)
  end
end
