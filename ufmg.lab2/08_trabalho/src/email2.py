import log
import smtplib

EMAIL_DESTINO = "viniciusfc95@gmail.com"
EMAIL_ORIGEM = "pma-lab2-engsis@bol.com.br"
EMAIL_ASSUNTO = "Senha gerada"
EMAIL_SENHA = "aAN1S9U*"

def send_mail(text):
    message = "Subject: {}\n\n{}".format(EMAIL_ASSUNTO, text)
    server = smtplib.SMTP("smtps.bol.com.br", 587)
    server.starttls()
    server.login(EMAIL_ORIGEM, EMAIL_SENHA)
    server.sendmail(EMAIL_ORIGEM, EMAIL_DESTINO, message)
    server.quit()

def enviarEmail(senhaGerada):
    log.logar("Enviar E-mail: " + str(senhaGerada))
    send_mail("Senha: " + str(senhaGerada))