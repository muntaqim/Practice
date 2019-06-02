def from_string(string):
        new_list = string.split('-')
        pattern= list()
        for word in new_list:
            if word == 'dash':
                pattern += ['_']
            elif word == 'dot':
                pattern += ['.']
            
        return pattern




print from_string("dot-dash-dash-dot");
