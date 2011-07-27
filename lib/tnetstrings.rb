require File.expand_path('../ext/tnetstrings', File.dirname(__FILE__))

module TNETS
  extend self

  def load(str)
    c_parse(str)
  end

  def dump(obj, *a)
    obj.to_tnets(*a)
  end
end

class TrueClass
  TO_TNETS = '4:true!'

  def to_tnets(*)
    TO_TNETS
  end
end

class FalseClass
  TO_TNETS = '5:false!'
  def to_tnets(*)
    TO_TNETS
  end
end

class NilClass
  TO_TNETS = '0:~'
  def to_tnets(*)
    TO_TNETS
  end
end

class String
  def to_tnets(*)
    "#{size}:#{self},"
  end
end

class Fixnum
  def to_tnets(*)
    "#{to_s.size}:#{self}#"
  end
end

module Enumerable
  def to_tnets(*a, &b)
    return each_tnets(&b) if block_given?

    out = ''
    each { |x| out << x.to_tnets(*a) }
    "#{out.size}:#{out}]"
  end

  def stream_tnets(io=$stdout)
    each_tnets { |x| io << x }
  end

  def each_tnets
    each { |x| yield x.to_tnets }
  end
end

class Hash
  def to_tnets(*)
    out = ''
    each do |k, v|
      # symbols don't respond to :to_str for some reason
      k = k.to_s if k.is_a? Symbol

      unless k.respond_to? :to_str
        raise TNETS::DumpError, "only string-like objects are allowed as keys"
      end

      out << k.to_str.to_tnets
      out << v.to_tnets
    end

    "#{out.size}:#{out}}"
  end
end

class Object
  def to_tnets(*a, &b)
    if respond_to? :as_tnets
      as_tnets(*a).to_tnets
    elsif respond_to? :as_json
      as_json(*a).to_tnets
    else
      method_missing(:to_tnets, *a, &b)
    end
  end
end
