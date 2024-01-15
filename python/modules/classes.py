#Define a class. Input args given in def __init__ list along with "self".
#Classes can also have other members and member/object functions
class Person:
    def __init__(self,name):
        self.name = name
    x=137
    def greet(self):
        print("皆さん今晩は！名前は" + self.name + "です。")

#Class "Scientist" inherits "Person"
#N.B. this class has it's own __init__ => the parent's init won't be inherited!
#     -- need to list everything from scratch
#     However, the desired members can be passed from parent to child via super 
class Scientist(Person):
    def __init__(self,name,field="Physics"):  #Do physics by default
        super().__init__(name)
        self.field = field
    def introduce(self):
        print(self.field+" is extremely interesting")

#Fill the application, start a new career.
def kneelAndDisconnect(researcher,job):
    researcher.field = job
    print(researcher.name+" has converted to "+job)

#A class def. must include something (otherwise whitespace problems)
#but if no members can be given now (e.g. WIP or debugging purposes), use:
class emptyClass:
    pass
