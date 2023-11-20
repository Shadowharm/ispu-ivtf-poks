class CubicSpline{
    constructor(points){
        this.dx = this.calcDx(points);
        this.derivatives = this.calcDerivatives(points, this.dx)
        this.equations = this.calcEquations(this.derivatives, points, this.dx);
    }
    
    getY(x){
        const func = (x, e) => {
            return (e.a + e.b*x + e.c*sq(x) + e.d*Math.pow(x,3));
        };

        for(let equation of this.equations){
            if(equation.x1 <= x && equation.x2 >= x){
                  const normalized = x - equation.x1; // map(x, equation.x1, equation.x2, 0, 1)
                  return func(normalized, equation);
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

    calcDerivatives(points, deltaX){    
        const outerDiagonal = dx => dx.map((delta) => 1 / delta);
        function middleDiagonal(dx){
            let array = [2/dx[0]];
            for(let i = 1; i < dx.length; i++){
                array.push(2 / dx[i-1] + 2 / dx[i])
            }
            array.push(2/dx[dx.length-1]);
            return array;
        }
        function getY(points, dx){
            let n = points.length - 1;
            let array = [3*(points[1].y - points[0].y)/sq(dx[0])];
            for(let i = 2; i <= n; i++){
                array.push(3*(points[i].y - points[i-1].y)/sq(dx[i-1]) + 3*(points[i-1].y - points[i-2].y)/sq(dx[i-2]));
            }
            array.push(3*(points[n].y - points[n-1].y)/sq(dx[n-1]));
            return array;
        }

        return solveTridiagonal(outerDiagonal(deltaX), middleDiagonal(deltaX),
                                             outerDiagonal(deltaX), getY(points, deltaX));
    }

    calcEquations(derivatives, points, dx){
        let equations = [];
        for(let i = 0; i < points.length-1; i++){
            const y = points[i].y;
            const y2 = points[i+1].y;
            const D = derivatives[i];
            const D2 = derivatives[i+1];
            
            equations.push({
                x1: points[i].x,
                x2: points[i+1].x,
                a: y,
                b: D,
                c: 3*(y2-y)/sq(dx[i])-2*D/dx[i]-D2/dx[i],
                d: 2*(y-y2)/(sq(dx[i])*dx[i])+D/sq(dx[i])+D2/sq(dx[i]),
            })
        }
        return equations;
    }

}