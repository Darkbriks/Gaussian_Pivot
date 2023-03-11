class LinearEquation:
    def __init__(self, dict, nb_var):
        self.equation = dict
        self.nb_var = nb_var

    def __str__(self):
        for i in self.equation.keys():
            print(i, self.equation[i], " +", end=" ")