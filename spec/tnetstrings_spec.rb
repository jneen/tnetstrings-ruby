require './lib/tnetstrings'

describe TNETS do
  context "successful examples" do
    it "parses a string" do
      TNETS.load("3:,abc").should == "abc"
    end

    it "parses null" do
      TNETS.load("0:~").should == nil
    end

    it "parses true" do
      TNETS.load("4:!true").should == true
    end

    it "parses false" do
      TNETS.load("5:!false").should == false
    end

    it "parses a number" do
      TNETS.load("2:#32").should == 32
    end

    it "parses an array" do
      TNETS.load("10:]2:#322:#84").should == [32, 84]
    end

    it "parses a dict" do
      pending "implementation"
      TNETS.parse(%[16:}1:,a1:#11:,b1:#2]).should == {:a => 1, :b => 2}
    end
  end

  context "error cases" do
  end
end
