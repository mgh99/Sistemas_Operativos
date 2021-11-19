
import { Db } from "mongodb";
import { getDocuments } from "./populated";
import express from "express";
import {freeseats,register,free, signin, login} from "./resolvers";
import { nextTick } from "process";

const bodyParser = require("body-parse");

const run = async () => {

  const db: Db = await getDocuments();//ya me devuelve la base de datos ya conectada
  const app = express(); //inicio el servidor
  app.set("db", db); //asocio el nombre db a la cte de db

  ///Los USE : funciones que las usamos de seguratas (VALIDACION PARA QUE FUNCIONE MAS TARDE LA FUNCION)
  app.use("/freeseats" , (req,res,next)=>{
    if(parseInt((req.query.dia as string))<0 || parseInt((req.query.dia as string))>31 || parseInt((req.query.mes as string))<0 || parseInt((req.query.mes as string))>12){
      res.sendStatus(505);
    }else{
      next(); //es ir a la funcion que hemos llamado
    }
  })

  app.use("/book",(req,res,next)=>{
    if(parseInt((req.query.dia as string))<0 || parseInt((req.query.dia as string))>31 || parseInt((req.query.mes as string))<0 || parseInt((req.query.mes as string))>12
    || parseInt((req.query.seat as string))<0 || parseInt((req.query.seat as string))>20){
      res.sendStatus(505);
    }else{
      next();
    }
  })

  app.use("/FREE",(req,res,next)=>{
    if(parseInt((req.query.dia as string))<0 || parseInt((req.query.dia as string))>31 || parseInt((req.query.mes as string))<0 || parseInt((req.query.mes as string))>12
    || parseInt((req.query.seat as string))<0 || parseInt((req.query.seat as string))>20 || !req.headers.token ){
      res.sendStatus(505);
    }else{
      next();
    }
  })

  app.use("/signin", (req, res, next) => {
    if(!req.body.email || !req.body.contraseña ){
      res.sendStatus(404).send("Completa los campos vacíos");
    }else{
      next();
    }
  })

  // app.use("/login", (req, res, next) => {
  //   if((req.body.email  != email) || req.body.contraseña != contraseña ){
  //     res.sendStatus(404).send("Datos incorrectos");
  //   }else{
  //     next();
  //   }
  // })

  app.use(bodyParser.json());
  app.use(bodyParser.urlencoded({extended:true}));

  ///GETs ->obtener
  app.get("/status", async (req, res) => {
    const date= new Date();
    res.status(200).send(`DATE: ${date.getDate()} - ${date.getMonth()} - ${date.getUTCFullYear()}`);
  });
  app.get("/freeseats", freeseats);

  ///POSTs -> subir 
  app.post("/book", register);// hecho por query
  app.post("/FREE", free);
  app.post("/signin", signin);
  app.post("/login", login);

  await app.listen(3000);
};

/// estoy corriendo esto
try {
  run();
} catch (e) {
  console.error(e);
}