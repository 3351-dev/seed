// // index.js

// const koa = require('koa')
// const app = new koa()

// app.use(ctx =>{
// 	ctx.body='Hello Koa 22233'
// })

// app.listen(4000,()=>{
// 	console.log('3351 server is listening to port 4000')
// })


const koa = require('koa')
const koaRouter = require('koa-router')

const app = new koa()
const router = new koaRouter()

router.get('/', (ctx, next)=>{
	ctx.body = 'home'
})

router.get('/about', (ctx, next)=>{
	ctx.body = 'About'
})

router.get('/about/:name', (ctx, next)=>{
	// :param => ctx.params안에 설정
	const {name} = ctx.params
	ctx.body = 'About '+name
})

router.get('/post',(ctx,next)=>{
	const {id} = ctx.request.query
	if(id){
		ctx.body = 'Post #'+id
	}else{
		ctx.body = 'non post'
	}
})

app.use(router.routes())
app.use(router.allowedMethods())

app.listen(4000,()=>{
	console.log("3351 Server, port 4000")
})