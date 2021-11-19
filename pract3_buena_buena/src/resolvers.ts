import { v4 as uuidv4 } from "uuid";
import { query, Request, Response } from "express";
import { Db } from "mongodb";
import { Documentos, Usuario } from "./types";

export const freeseats = async (req: Request, res: Response) => {
  const db: Db = req.app.get("db"); //base de datos en la que mi solicitud se conecta a la base de datos que tenga con ese nombre -> AÑADIRLO SIEMPRE

  /*SI NO PONGO EL AWAIT NO ESPERA Y SE PUEDE QUEDAR VACIO*/
  //los await son esperas (promesas) que no se ven
  const puest: Documentos[] = (await db //Como quiero ver los documentos
    .collection("Documentos")
    .find({ day: parseInt((req.query.dia as string)), month: parseInt((req.query.mes as string)), year: parseInt((req.query.año as string)) })
    .toArray() as Documentos[])//array de documentos

  let puestos: Array<number> = [];
  for (let i = 1; i <= 20; i++) puestos.push(i);
  puest.forEach(elem => { //Buscar dentro del array de documentos
    puestos = puestos.filter(num => num !== elem.seat); //filtro los disponibles
  })
  res.status(200).json(puestos);//devuelvo el json de los puestos filtrados, que son los disponibles
};

export const register = async (req: Request, res: Response) => {
  const db: Db = req.app.get("db");
  const reservas: Documentos[] = (await db.collection("Documentos")
    .find({ day: parseInt((req.query.dia as string)), month: parseInt((req.query.mes as string)), year: parseInt((req.query.año as string)) })
    .toArray() as Documentos[])

  reservas.forEach(paraCadaReserva => {
    if (paraCadaReserva.seat == parseInt(req.query.seat as string)) { //
      //lo que esta en $ es una variable que tengo que meter
      console.log(`${paraCadaReserva} - ${parseInt(req.query.seat as string)}`) //no es una resta es un guion
      res.sendStatus(404); //ERROR, porque la reserva que he intentado hacer ya esta hecha
      //en cuanto envias una respuesta se para SIEMPRE
    }
  })

  //El usuario mete todos sus datos y al ser query por parametros hay que pasarlo a int porque se trata de numeros
  const user: Documentos = {
    day: parseInt((req.query.dia as string)),
    month: parseInt((req.query.mes as string)),
    year: parseInt((req.query.año as string)),
    seat: parseInt((req.query.seat as string)),
    token: uuidv4()//funcion que te da el id
  }

  //ESTA LINEA ES NECESARIA Y PUNTO PORQUE LO DICE SANTI Y YA
  const chars = await db.collection("Documentos").insertOne(user);//Si lo inserta dice que todo correcto y si no sale NULL

  if (chars) {
    res.status(200).send(user);
  } else {
    res.send("algo ha");
  }
}

export const free = async (req: Request, res: Response) => {
  const db: Db = req.app.get("db"); //solicitud base de datos
  const id = req.params.id; //estoy metiendo en id lo que hay en parametros de mi solicitud llamado id

  //Se borra la que estoy buscando
  const char = await db.collection("Documentos").deleteOne(
    { day: parseInt((req.query.dia as string)), month: parseInt((req.query.mes as string)), year: parseInt((req.query.año as string)), token: req.headers.token }
  );

  //devuleve una pequeña estructura y te dice si la ha borrado o no
  if (char.deletedCount == 1) { //1 = es que lo ha borrado
    res.sendStatus(200);
  } else {
    res.sendStatus(404);
  }
}

//POSTMAN: tiene 3 formas de pasar datos 
/*
  1) params : /characters/:id = para filtrar por parametro
  2) query:   /characters = por la tabla de key value en postman 
  3) body:    /characters = se manda por la tabla de key value de body en postman 

*/


/***********************************************************
AQUI EMPIEZA LA PRACTICA 3 
CHAN
    CHAN
        CHAN!!!
*/
//******************************************************** */

export const signin = async (req: Request, res: Response) => {
  const db: Db = req.app.get("db");

  const user = await db.collection("Users").find({
    email: (req.body.email as string) //como lo necesito que sea un string en el mongo lo guardo como string porque sino es de tipo any
  });

  if (user)// es lo mismo que user != NULL
  {
    res.send("Usuario ya registrado").status(409);
  }

  const usuario: Usuario = {
    email: (req.body.email as string),
    contraseña: (req.body.contraseña as string),
    token: uuidv4()
  };

  const chars = await db.collection("Users").insertOne(usuario);

  if (chars) {
    res.status(200).send(usuario);
  } else {
    res.send("Algo ha ido mal");
  }

}

//login = si el usuario y la contraseña son correctos entonces se puede entrar
export const login = async (req: Request, res: Response) => {
  const db: Db = req.app.get("db");

  const user = await db.collection("Users").find({
    email: (req.body.email as string),
    contraseña: (req.body.contraseña as string)
  });

  if(user) {

  }




}

