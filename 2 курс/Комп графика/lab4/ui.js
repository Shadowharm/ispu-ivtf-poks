class UI{
    constructor(client){
        this.client = client;
        this.transforms = [];
        this.box = document.getElementById('transforms-box');
        

        this.angleInput = document.getElementById('angle');
        this.xInput = document.getElementById('x');
        this.yInput = document.getElementById('y');
        this.dxInput = document.getElementById('dx');
        this.dyInput = document.getElementById('dy');
        this.sxInput = document.getElementById('sx');
        this.syInput = document.getElementById('sy');
        this.aInput = document.getElementById('a');
        this.bInput = document.getElementById('b');
        this.cInput = document.getElementById('c');
        this.dInput = document.getElementById('d');

        const addRotationButton = document.getElementById('add-rotation-button');
        const addTranslateButton = document.getElementById('add-translate-button');
        const addScaleButton = document.getElementById('add-scale-button');
        const addSkewButton = document.getElementById('add-skew-button');
        const canvas = document.getElementById('canvas');
        let x = 0
        let y = 0
        const dragElement = e => {
            // this.addTransform({type: 'translate', x: e.movementX, y: e.movementY});
            x += e.movementX
            y += e.movementY
            this.transforms[this.transforms.length - 1] = {type: 'translate', x, y}
            this.updateViewBox();
        }

        canvas.addEventListener('mousedown', (e) => {
            this.addTransform({type: 'translate', x: 0, y: 0});
            canvas.addEventListener('mousemove', dragElement)
        })

        canvas.addEventListener('mouseup', () => {
            x = 0
            y = 0
            canvas.removeEventListener('mousemove', dragElement)
        })

        canvas.addEventListener('mouseleave', () => {
            x = 0
            y = 0
            canvas.removeEventListener('mousemove', dragElement)
        })

        addRotationButton.onclick = () => {
            this.addTransform({type: 'rotate', x: +this.xInput.value, y: +this.yInput.value, angle: +this.angleInput.value});
        }
        
        addTranslateButton.onclick = () => {
            this.addTransform({type: 'translate', x: +this.dxInput.value, y: +this.dyInput.value});
        }
        
        addScaleButton.onclick = () => {
            this.addTransform({type: 'scale', x: +this.sxInput.value, y: +this.syInput.value});
        }
        addSkewButton.onclick = () => {
            this.addTransform({type: 'skew', a: +this.aInput.value, b: +this.bInput.value, c: +this.cInput.value, d: +this.dInput.value});
        }

        this.deleteTransform = this.deleteTransform.bind(this);
        this.renderTransform = this.renderTransform.bind(this);
    }

    addTransform(transform){
        this.transforms.push(transform);
        this.updateViewBox();
    }

    deleteTransform(i){
        this.transforms.splice(i, 1);
        this.updateViewBox();
    }

    updateViewBox(){
        this.client(this.transforms);
        while (this.box.firstChild) {
            this.box.removeChild(this.box.firstChild);
        }

        this.transforms.map(this.renderTransform)
    }

    renderTransform(transform, i){
        const transformElement = document.createElement('div');

        const button = document.createElement('button');
        button.innerHTML = 'X';
        button.onclick = () => {
            this.deleteTransform(i);
        }

        const name = document.createElement('i');
        name.innerHTML = transform.type;

        const params = document.createElement('span');
        if (transform.type === 'skew') {
            params.innerHTML = [transform.a, transform.b, transform.c, transform.d].join(', ')
        } else {
            params.innerHTML = transform.type == 'rotate' ? 
            transform.angle+", " : "";
            params.innerHTML += transform.x + ", " + transform.y;

        }

        transformElement.appendChild(button);
        transformElement.appendChild(name);
        transformElement.appendChild(params);
        this.box.appendChild(transformElement);
    }
}