require './lib/tnetstrings'

describe TNETS do
  context "parsing" do
    context "successful examples" do
      it "parses a string" do
        TNETS.load("3:abc,").should == "abc"
      end

      it "parses null" do
        TNETS.load("0:~").should == nil
      end

      it "parses true" do
        TNETS.load("4:true!").should == true
      end

      it "parses false" do
        TNETS.load("5:false!").should == false
      end

      it "parses a number" do
        TNETS.load("2:32#").should == 32
      end

      it "parses a negative number" do
        TNETS.load("3:-32#").should == -32
      end

      it "parses an array" do
        TNETS.load("17:2:32#2:84#4:true!]").should == [32, 84, true]
      end

      it "parses a dict" do
        TNETS.load(%[16:1:a,1:1#1:b,1:2#}]).should == {:a => 1, :b => 2}
      end
    end

    context "degenerate cases" do
      it "parses an empty dict" do
        TNETS.load(%|0:}|).should == {}
      end

      it "parses an empty array" do
        TNETS.load(%|0:]|).should == []
      end

      it "parses an empty string" do
        TNETS.load(%|0:,|).should == ''
      end

      it "parses an empty bool" do
        TNETS.load(%|0:!|).should == false
      end
    end

    context "error cases" do
      def expect_error(str, *args)
        expect { TNETS.load(str) }
          .to raise_error(TNETS::ParserError, *args)
      end

      context "length spec" do
        it "requires digits at the front" do
          expect_error("abc:true!")
        end

        it "requires a colon before the 10th character" do
          expect_error("12345678901:true!")
        end

        it "requires a valid symbol at the end" do
          expect_error("1:f")
        end

        it "requires the data to be at least as long as the length spec" do
          expect_error("100:true!")
        end
      end

      context "null" do
        it "requires the length to be zero" do
          expect_error("1:x~")
        end
      end

      context "bool" do
        it "returns false given anything but true" do
          TNETS.load("4:trub!").should == false
          TNETS.load("6:sdflkj!").should == false
          TNETS.load("4:true!").should == true
        end
      end

      context "number" do
        it "requires digits only" do
          expect_error("3:1bc#")
        end
      end

      context "array" do
        it "requires sane lengths" do
          expect_error("5:10:abcde,]")
        end
      end

      context "dict" do
        it "requires sane lengths" do
          expect_error("13:1:a,10:abcde,}")
        end

        it "requires keys to be strings" do
          # { 1 => 2 }
          expect_error("8:1:1#1:2#}")
          # { nil => 2 }
          expect_error("7:0:~1:2#}")
          # { false => 2 }
          expect_error("7:0:!1:2#}")
        end

        it "requires a balanced hash" do
          # one item only
          # { :a => }
          expect_error("4:1:,a}")

          # three items
          # { :a => 1, :b => }
          expect_error("12:1:a,1:1#1:b,}")
        end
      end
    end
  end

  context "dumping" do
    it "dumps a string" do
      "abc".to_tnets.should == "3:abc,"
      TNETS.load(TNETS.dump("abc")).should == "abc"
    end

    it "dumps a number" do
      34.to_tnets.should == "2:34#"
      TNETS.load(TNETS.dump(34)).should == 34
    end

    it "dumps nil" do
      nil.to_tnets.should == '0:~'
      TNETS.load(TNETS.dump(nil)).should == nil
    end

    it "dumps true and false" do
      true.to_tnets.should == '4:true!'
      false.to_tnets.should == '5:false!'
      TNETS.load(TNETS.dump(true)).should == true
      TNETS.load(TNETS.dump(false)).should == false
    end

    it "dumps an array" do
      arr = [1, true, "three", nil]
      arr.to_tnets.should == '22:1:1#4:true!5:three,0:~]'
      TNETS.load(TNETS.dump(arr)).should == arr
    end

    it "streams an enumerable" do
      sio = StringIO.new
      enum = Class.new do
        include Enumerable
        def each(&b)
          [1, true, "three", nil].each(&b)
        end
      end.new

      enum.stream_tnets(sio)
      sio.string.should == enum.map(&:to_tnets).join
    end

    it "dumps a hash" do
      hsh = { :a => 1, :b => true, :c => "three", :d => nil }
      hsh.to_tnets.should == '38:1:a,1:1#1:b,4:true!1:c,5:three,1:d,0:~}'
      TNETS.load(TNETS.dump(hsh)).should == hsh
    end
  end
end
