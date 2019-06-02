import random


class Die:
    def __init__(self, sides=2):
        if sides < 2:
            raise ValueError("Can't have fewer than two sides")
        self.sides = sides
        self.value = random.randint(1, sides)
        
    def __int__(self):
        return self.value
      
    def __add__(self, other):
        return int(self) + other
    
    def __radd__(self, other):
        return self + other
    
class D20(Die):
    def __init__(self):
        super().__init__(20)
        


class Hand(list):
    def __init__(self, size=0, die_class=None, *args, **kwargs):
        if not die_class:
            raise ValueError("Need die class")
        super().__init__(self,*args,**kwargs)
        
        for _ in range(size):
            self.append(die_class())
            
    @property
    def total(self):
        return sum(self)
    
    @classmethod
    def roll(cls, size):
        return cls(size=size, die_class=D20)


