class Pivot {
    constructor(line = 0, value = 0) {this.line = line; this.value = value;}
    
    toString() {return this.line + " " + this.value;}
    
    toHTML() {return this.line + " " + this.value;}
    
    toLatex() {return this.line + " " + this.value;}
    
    getLine() {return this.line;}
    
    getValue() {return this.value;}
    
    setLine(line) {this.line = line;}
    
    setValue(value) {this.value = value;}
}

class Coefficient {
    constructor(variable = "a", value = 0) {this.variable = variable; this.value = value;}
    
    toString() {return this.value + this.variable;}
    
    toHTML() {return this.value + this.variable;}
    
    toLatex() {return this.value + this.variable;}
    
    getVariable() {return this.variable;}
    
    getValue() {return this.value;}
    
    setVariable(variable) {this.variable = variable;}
    
    setValue(value) {this.value = value;}
    
    isZero() {return this.value === 0;}
}

class LinearEquation {
    constructor(equation = [Coefficient], independent = 0, nb_coefficients = 0) {this.equation = equation; this.independent = independent; this.nb_coefficients = nb_coefficients;}
    
    toString() {
        let str = "";
        for (let i = 0; i < this.nb_coefficients; i++) {
            str += this.equation[i].toString();
            if (i < this.nb_coefficients - 1) str += " + ";
            else str += " = ";
        }
        str += this.independent;
        return str;
    }
    
    toHTML() {
        let str = "";
        for (let i = 0; i < this.nb_coefficients; i++) {
            str += this.equation[i].toHTML();
            if (i < this.nb_coefficients - 1) str += " + ";
            else str += " = ";
        }
        str += this.independent;
        return str;
    }
    
    toLatex() {
        let str = "";
        for (let i = 0; i < this.nb_coefficients; i++) {
            str += this.equation[i].toLatex();
            if (i < this.nb_coefficients - 1) str += " + ";
            else str += " = ";
        }
        str += this.independent;
        return str;
    }
    
    getEquation() {return this.equation;}
    
    getIndependent() {return this.independent;}
    
    getNbCoefficients() {return this.nb_coefficients;}
    
    getIndexOfVariable(variable) {
        for (let i = 0; i < this.nb_coefficients; i++) {
            if (this.equation[i].getVariable() === variable) return i;
        }
        return -1;
    }
    
    setEquation(equation) {this.equation = equation;}
    
    setIndependent(independent) {this.independent = independent;}
    
    setNbCoefficients(nb_coefficients) {this.nb_coefficients = nb_coefficients;}
    
    addCoefficient(coefficient, index = this.nb_coefficients) {
        if (index < 0 || index > this.nb_coefficients) throw new Error("Index out of bounds");
        this.equation.splice(index, 0, coefficient);
        this.nb_coefficients++;
    }
    
    isZero() {return this.nb_coefficients === 0;}
    
    // true if only one coefficient is not zero
    isSolvable() {
        let count = 0;
        for (let i = 0; i < this.nb_coefficients; i++) {
            if (!this.equation[i].isZero()) count++;
        }
        return count === 1;
    }
    
    solve() {
        if (!this.isSolvable()) throw new Error("Equation is not solvable");
        for (let i = 0; i < this.nb_coefficients; i++) {
            if (!this.equation[i].isZero()) return this.independent / this.equation[i].getValue();
        }
        return 0;
    }
    
    replaceCoefficientByValue(value, variable) {
        for (let i = 0; i < this.nb_coefficients; i++) {
            if (this.equation[i].getVariable() === variable) {
                this.independent += this.equation[i].getValue() * value;
                this.equation.splice(i, 1);
                this.nb_coefficients--;
            }
        }
    }
    
    divideByCoefficient(divider) {
        for (let i = 0; i < this.nb_coefficients; i++) {this.equation[i].setValue(this.equation[i].getValue() / divider);}
        this.independent /= divider;
    }
    
    multiplyByCoefficient(multiplier) {
        for (let i = 0; i < this.nb_coefficients; i++) {this.equation[i].setValue(this.equation[i].getValue() * multiplier);}
        this.independent *= multiplier;
    }
    
    addEquation(equation) {
        for (let i = 0; i < equation.getNbCoefficients(); i++)
        {
            if (this.getIndexOfVariable(equation.getEquation()[i].getVariable()) === -1) {this.addCoefficient(equation.getEquation()[i]);}
            else {this.equation[this.getIndexOfVariable(equation.getEquation()[i].getVariable())].setValue(this.equation[this.getIndexOfVariable(equation.getEquation()[i].getVariable())].getValue() + equation.getEquation()[i].getValue());}
        }
        this.independent += equation.getIndependent();
    }
    
    subtractEquation(equation) {
        for (let i = 0; i < equation.getNbCoefficients(); i++)
        {
            if (this.getIndexOfVariable(equation.getEquation()[i].getVariable()) === -1) {this.addCoefficient(equation.getEquation()[i]);}
            else {this.equation[this.getIndexOfVariable(equation.getEquation()[i].getVariable())].setValue(this.equation[this.getIndexOfVariable(equation.getEquation()[i].getVariable())].getValue() - equation.getEquation()[i].getValue());}
        }
        this.independent -= equation.getIndependent();
    }
}

class LinearSystem {
    constructor(system = [], nb_equations = 0, nb_variables = 0, name = "S") {
        this.system = system;
        this.nb_equations = nb_equations;
        this.nb_variables = nb_variables;
        this.name = name;
    }
    
    toString() {
        let str = this.name + " ; " + this.nb_equations + " equations ; " + this.nb_variables + " variables\n";
        for (let i = 0; i < this.nb_equations; i++) {
            str += this.system[i].toString() + "\n";
        }
        return str;
    }
    
    toHTML() {
        let str = this.name + " ; " + this.nb_equations + " equations ; " + this.nb_variables + " variables<br>";
        for (let i = 0; i < this.nb_equations; i++) {
            str += this.system[i].toHTML() + "<br>";
        }
        return str;
    }
    
    toLatex() {
        let str = this.name + " ; " + this.nb_equations + " equations ; " + this.nb_variables + " variables\\\\";
        for (let i = 0; i < this.nb_equations; i++) {
            str += this.system[i].toLatex() + "\\\\";
        }
        return str;
    }
    
    getSystem() {return this.system;}
    
    getNbEquations() {return this.nb_equations;}
    
    getNbVariables() {return this.nb_variables;}
    
    getName() {return this.name;}
    
    setSystem(system) {this.system = system;}
    
    setNbEquations(nb_equations) {this.nb_equations = nb_equations;}
    
    setNbVariables(nb_variables) {this.nb_variables = nb_variables;}
    
    setName(name) {this.name = name;}
    
    addEquation(equation, index = this.nb_equations) {
        if (index < 0 || index > this.nb_equations) throw new Error("Index out of bounds");
        this.system.splice(index, 0, equation);
        this.nb_equations++;
    }
    
    isZero() {return this.nb_equations === 0 || this.nb_variables === 0;}
}