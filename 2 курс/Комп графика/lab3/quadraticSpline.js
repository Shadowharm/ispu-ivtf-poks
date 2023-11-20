class QuadraticSpline{
    constructor(points){
        this.dx = this.calcDx(points);
        this.derivatives = this.calcDerivatives(points, this.dx)
        this.equations = this.calcEquations(this.derivatives, points, this.dx);
        this.selfCheck();
    }

    getY(x){
        const func = (x, e) => {
            return (e.a + e.b*x + e.c*sq(x));
        };

        for(let equation of this.equations){
            if(equation.x1 <= x && equation.x2 >= x){
                  const t = x - equation.x1; // map(x, equation.x1, equation.x2, 0, 1)
                  return func(t, equation);
            }
        }

        return NaN;
    }

    calcDx(points){
        const dx = [];
        for(let i = 1; i < points.length; i++){
            dx.push(points[i].x - points[i-1].x);
        }
        return dx;
    }

    calcDerivatives(points, dx){    
        const D = [0];
        for(let i = 1 ; i < points.length; i++){
            D.push(2*(points[i].y-points[i-1].y)/(dx[i-1]) - D[i-1]);
        }
        return D;
    }

    calcEquations(derivatives, points, dx){
        let equations = [];
        for(let i = 0; i < points.length-1; i++){
            const y = points[i].y;
            const D = derivatives[i];
            const D2 = derivatives[i+1];
            
            equations.push({
                x1: points[i].x,
                x2: points[i+1].x,
                a: y,
                b: D,
                c: (D2 - D) / (2*dx[i])
            })
        }
        return equations;
    }

    selfCheck(){
        const func = (x, e) => {
            return (e.a + e.b*x + e.c*sq(x));
        };

        const xp = (x, e) => {
            return (e.b + 2*e.c*x);
        };

        for(let i = 1; i < this.equations.length; i++){
            // sconsole.log(xp(0, this.equations[i]), xp(this.dx[i-1], this.equations[i-1]));
        }
    }
}