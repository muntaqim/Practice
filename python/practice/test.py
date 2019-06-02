class Letter:
    def __init__(self, pattern=None):
        self.pattern = pattern
      
    def __iter__(self):
        yield from self.pattern
      
    def __str__(self):
        output = []
        for blip in self:
            if blip == '.':
                output.append('dot')
            else:
                output.append('dash')
        return '-'.join(output)
    
    @classmethod
    def from_string(cls, string):
        new_list = string.split('-')
        pattern= list()
        for word in new_list:
        	if word == 'dash':
                pattern += ['_']
            elif word == 'dot':
                pattern += ['.']
                
        return self(pattern)
    

class S(Letter):
    def __init__(self):
        pattern = ['.', '.', '.']
        super().__init__(pattern)
